# AppArmor

See:
* [Debian Handbook](https://debian-handbook.info/browse/stable/sect.apparmor.html)
* [AppArmor Website](https://apparmor.net/)

Contents:
- [AppArmor](#apparmor)
  - [01. Introduction](#01-introduction)
  - [02. Installation](#02-installation)
  - [03. Viewing Profile Status](#03-viewing-profile-status)
  - [04. Creating a new Profile](#04-creating-a-new-profile)


## 01. Introduction

* AppArmor allows for permissions and policy on applications.
* Proactively protects the OS and applications from external or internal threats, and zero-day attacks.
* AppArmor is a Debian alternative to the security architecture [SELinux](https://www.redhat.com/en/topics/linux/what-is-selinux) (Security Enhanced Linux). i.e. Redhat, Centos, Fedora.
* AppArmor is considered simpler and easier for individual machines, and easier to review.
* Whereas SELinux can create complete and complex policies and manage them via external server.
* AppArmor profiles are stored under: `/etc/apparmor.d/`

## 02. Installation

AppArmor is built into standard kernels provided by Debian.

You can install using:
```bash
sudo apt install apparmor apparmor-profiles apparmor-utils
```

To check the status, use commands such as:
```bash
systemctl status apparmor  # Checks status of the AppArmor service and tells you if it is enabled on boot
systemctl start apparmor   # Starts the service
systemctl enable apparmor  # Makes apparmor start on boot
systemctl disable apparmor # Stop
```

## 03. Viewing Profile Status

View status of profiles
```bash
sudo aa-status
```

Profile modes:
* Enforce - deny if rule does not validate
* Complain - notifies and logs if rule does not validate
* Unconfined - not paying attention


You can view all processes with the unconfined mode using:
```bash
sudo aa-unconfined
sudo aa-unconfined --paranoid # All process that have at least one active network connection
```



We can change the mode of a profile using one of the commands:
```bash
sudo aa-complain /home/mark/myscript.sh
sudo aa-enforce /home/mark/myscript.sh
sudo aa-disable /home/mark/myscript.sh
# ...etc
```


## 04. Creating a new Profile

Use aa-genprof to create a profile.
```bash
sudo aa-genprof myscript.sh
```

While open, run the program, then press S to scan events.

For each permission event, we have a set of choices available:
* Inherit = Inherits this permission from parent
* Named/Profile = Inherit this permission from another profile by name
* Child = Transition to a subprofile/child-profile of the current process

```
sudo vim /etc/apparmor.d/home.mark.Code.general-linux-practice.AppArmor.examples.a.out
sudo apparmor_parser -r /etc/apparmor.d/home.mark.Code.general-linux-practice.AppArmor.examples.a.out
./a.out hello.txt
```