# AppArmor CheatSheet

See:
* [AppArmor profile language docs](https://gitlab.com/apparmor/apparmor/-/wikis/QuickProfileLanguage)

Contents:
- [AppArmor CheatSheet](#apparmor-cheatsheet)
  - [Status commands](#status-commands)
  - [Viewing commands](#viewing-commands)
  - [Profile manipulation](#profile-manipulation)
  - [Permissions](#permissions)

## Status commands

Purpose                 | Command/s
------------------------|------------------------
Check status of aa      | `systemctl status apparmor`
Starts the service      | `systemctl start apparmor`
Enables start + on boot | `systemctl enable apparmor`
Stop apparmor           | `systemctl disable apparmor`


## Viewing commands

Purpose                                           | Command/s
--------------------------------------------------|------------------------
View profiles                                     | `sudo aa-status`
View unconfined processes                         | `sudo aa-unconfined`
View unconfined with 1+ active network connection | `sudo aa-unconfined --paranoid`
View denials                                      | `aa-notify -s 1 -v`
Turn on desktop notifications                     | `aa-notify -p`

Check out:
* `sudo apparmor_parser --help`
* `sudo apparmor_status --help`

## Profile manipulation

Purpose                                           | Command/s
--------------------------------------------------|------------------------
Create profile using genprof                      | `sudo aa-genprof <EXECUTABLE>`
Create profile skeleton using easyprof            | `aa-easyprof <EXECUTABLE> > <FILENAME> `
Reload profile                                    | `apparmor_parser -r <PROFILE>`
.                                                 | `sudo aa-disable <PROFILE> && sudo aa-enforce <PROFILE>`
Change profile to complain mode                   | `sudo aa-complain <PROFILE>`
Update a profile using aa-logprof                 | `sudo aa-logprof`

## Permissions

Permission choices:
* **Inherit**
  * Creates a rule that is denoted by “ix” within the profile
  * Causes the executed binary to inherit permissions from the parent profile.
* **Child**
  * Creates a rule that is denoted by “Cx” within the profile.
  * Requires a sub-profile to be created within the parent profile and rules must be separately generated for this child.
  * (prompts will appear when running scans on the parent)
* **Deny**
  * Creates a rule that AppArmor prepends with “deny” at the start of the line within the profile
  * Causes the parents access to the resource be denied.
* **Abort**
  * Exits the AppArmor program without saving any changes.
* **Finish**
  * Exits the AppArmor program but WILL save changes.

Permission choices

Execute permissions:
* ix - the new process should run under the current profile
* cx - the new process should run under a child profile that matches the name of the executable
* px - the new process should run under another profile that matches the name of the executable
* ux - the new process should run unconfined
* Capitalised letters (Px, Cx, Ux) should be used when developing profiles since they clean the environment and uses only the program profile

