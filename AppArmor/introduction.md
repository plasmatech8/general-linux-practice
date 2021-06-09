# Introduction to AppArmor

## Introduction

General:
* AppArmor allows for permissions and policy on applications.
* Proactively protects the OS and applications from external or internal threats, and zero-day attacks.
* AppArmor is a Debian alternative to the security architecture [SELinux](https://www.redhat.com/en/topics/linux/what-is-selinux) (Security Enhanced Linux). i.e. Redhat, Centos, Fedora.
* AppArmor is considered simpler and easier for individual machines, and easier to review.
* Whereas SELinux can create complete and complex policies and manage them via external server.
* AppArmor profiles are stored under: `/etc/apparmor.d/`

Discretionary Access Control:
* e.g. `-rw-rw-r-- 1 mark mark 331 Jun  9 12:48 writeprog.c`
* Property of a file
* Set by the owner of a file

Manditory Access Control:
* Process confined by a profile
* Set by the administrator

In Linux, MAC is provided by:
* SELinux / SEAndroid
* AppArmor
* SMACK
* TOMOYO

In AppArmor, processes are either confined, or unconfined.

If confined, a profile containing a whitelist of permission are required.

AppArmor can mediate access to:
* files and directories
* capabilities
* ptrace
* signals
* mount
* rlimits
* coarse-grained networking
* dbus
* unix sockets
* ...


## Resources

Debian:
* [Debian Handbook](https://debian-handbook.info/browse/stable/sect.apparmor.html)

AppArmor:
* [AppArmor Website](https://apparmor.net/)
* [AppArmor Official Docs](https://gitlab.com/apparmor/apparmor/-/wikis/Documentation)
* [AppArmor Official Profile Language Docs](https://gitlab.com/apparmor/apparmor/-/wikis/QuickProfileLanguage)

Ubuntu:
* [AppArmor Profile Tutorial](https://ubuntu.com/tutorials/beginning-apparmor-profile-development#1-overview)
* [AppArmor Manual](https://manpages.ubuntu.com/manpages/precise/en/man5/apparmor.d.5.html)

Suse:
* [AppArmor PDF Manual 2006](https://www.novell.com/documentation/apparmor/pdfdoc/apparmor2_admin/apparmor2_admin.pdf)
* [Profile Components and Syntax](https://documentation.suse.com/sles/15-SP1/html/SLES-all/cha-apparmor-profiles.html)

Videos:
* [Securing Applications with Apparmor](https://www.youtube.com/watch?v=0t-UZFBNyF0) by SecureRandom on YouTube

