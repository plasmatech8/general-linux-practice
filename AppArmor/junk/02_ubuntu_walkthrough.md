# Ubuntu Walkthrough

See:
* [How to create an AppArmor Profile](https://ubuntu.com/tutorials/beginning-apparmor-profile-development#1-overview) by Ubuntu

Contents:
- [Ubuntu Walkthrough](#ubuntu-walkthrough)
  - [01. Overview](#01-overview)
  - [02. Intro to profiles](#02-intro-to-profiles)
  - [03. Generating a basic profile](#03-generating-a-basic-profile)
  - [04. Denials and Complain Mode](#04-denials-and-complain-mode)
    - [View denials](#view-denials)
    - [Set to complain mode](#set-to-complain-mode)
  - [05. Using aa-logprof to refine a profile](#05-using-aa-logprof-to-refine-a-profile)
  - [06. Hand Editing the Profile](#06-hand-editing-the-profile)
  - [07. AppArmor Deny rules](#07-apparmor-deny-rules)

## 01. Overview

AppArmor is a MAC.

In this tutorial, we will generate a profile for certspotter.

## 02. Intro to profiles

Profiles are text files.

Access rules:
* r - read
* w - write
* m - memory map as executable
* k - file locking
* l - creation hard links
* ix - execution of other programs (inherits same policy)
* Px - is another which executes  under another profile after cleaning the environment

AppArmor Supports access controls for:
* files
* Linux capabilities
* network
* mount, remount and umount
* pivot_root
* ptrace
* signal
* DBus
* unix domain sockets

In addition:
* `${HOME}` variable exists and can be manipulated from tunables
* Explicit deny rules override allow rules
* Include files are supported to simplify profiles (i.e. `#include <abstractions/base>`, `#include <abstractions/nameservice>`, etc)

`sudo apt install apparmor-easyprof apparmor-notify apparmor-utils certspotter`

## 03. Generating a basic profile

Use `aa-easyprof` to generate a skeleton policy and move it to apparmor, then reload.
```bash
# Create skeleton policy
aa-easyprof /usr/bin/certspotter > usr.bin.certspotter

# Move to profiles and reload
sudo mv usr.bin.certspotter /etc/apparmor.d
sudo apparmor_parser -r /etc/apparmor.d/usr.bin.certspotter
```

Looks like:
```
# vim:syntax=apparmor
# AppArmor policy for certspotter
# ###AUTHOR###
# ###COPYRIGHT###
# ###COMMENT###

#include <tunables/global>

# No template variables specified

"/usr/bin/certspotter" {
  #include <abstractions/base>

  # No abstractions specified

  # No policy groups specified

  # No read paths specified

  # No write paths specified
}
```

We can now try certspotter and watch it fail:
```
$ certspotter
certspotter: /home/mark/.certspotter/watchlist: open /home/mark/.certspotter/watchlist: no such file or directory
```

## 04. Denials and Complain Mode

### View denials

Denials are logged to: `/var/log/syslog` (or `/var/log/audit/audit.log` for non-DBus policy violations if auditd is installed)

The kernel rate limits denials which might cause problems with profiling. This can be avoided by
installing auditd or adjusting the rate limit: `sudo sysctl -w kernel.printk_ratelimit=0`.

Another way to view denials is by using `aa-notify`.

This will report denials by consulting the logs. To show denials within the last day:
`/usr/bin/aa-notify -s 1 -v`.

And we can turn on desktop notifications using `-p`/`--poll` flag.

### Set to complain mode

Set: `sudo aa-complain certspotter`

## 05. Using aa-logprof to refine a profile

Use `sudo aa-logprof`

We will get something like:
```
Reading log entries from /var/log/syslog.
Updating AppArmor profiles in /etc/apparmor.d.
Complain-mode changes:

Profile: /usr/bin/certspotter
Path: /proc/sys/net/core/somaxconn
New Mode: r
Severity: 6

[1 - /proc/sys/net/core/somaxconn r,]
(A)llow / [(D)eny] / (I)gnore / (G)lob / Glob with (E)xtension / (N) ew / Audi(t) / Abo(r)t / (F)inish

A
```

This permission is read access to a file which specifies the maximium number of open socket
connections - so it is fine to allow it.

* `/proc/sys/net/core/somaxconn`
  * Max number of open socket connections
* `/etc/nsswitch.conf`
  * Certspotter uses the network to retrieve info from cert transparency logs
  * We can either allow this specific network access, or use an existing nameservice abstraction which grants common access patterns.
  * We can view the details under: `sudo vim /etc/apparmor.d/abstractions/nameservice`
* `/proc/sys/kernel/hostname`
  * There is no problem with letting the process know the hostname
* ...

## 06. Hand Editing the Profile

Lets go into the profile: `sudo vim /etc/apparmor.d/usr.bin.certspotter`

After editing we can reload the profile: `sudo apparmor_parser -r /etc/apparmor.d/usr.bin.certspotter`

## 07. AppArmor Deny rules

We can add explicit deny rules using:
```
owner @{HOME}/.certspotter/** rw,

deny @{HOME}/Documents/ rw,
deny @{HOME}/Private/ rw,
deny @{HOME}/Pictures/ rw,
deny @{HOME}/Videos/ rw,
deny @{HOME}/fake/ rw,
deny @{HOME}/.config/ rw,
deny @{HOME}/.ssh/ rw,
deny @{HOME}/.bashrc rw,
```

And reload:
```
sudo apparmor_parser -r /etc/apparmor.d/usr.bin.certspotter
```