# Examples

See:
* [Securing Applications with Apparmor](https://www.youtube.com/watch?v=0t-UZFBNyF0) by SecureRandom on YouTube
* [The Comprehensive Guide To AppArmor: Part 1](https://medium.com/information-and-technology/so-what-is-apparmor-64d7ae211ed)


## Example 1: C Program Writes to filesystem

We have `writeprog.c` C code:
```cs
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    FILE *fd;
    for (i=1; i<argc; i++) {
        fd = fopen(argv[i], "w");
        if (fd == NULL) {
            fprintf(stderr, "fopen failed for %s\n", argv[i]);
        }
        fprintf(fd, "This is written data in %s\n", argv[i]);
        fclose(fd);
    }
}
```

Which we can compile using: `gcc writeprog.c`

And execute using: `./a.out test.txt` (a file will be created)

To create a profile:
* Generate a profile: `sudo aa-genprof a.out`
* Run the executable: `./a.out test.txt`
* Press S to scan system logs for AppArmor events
* We will be asked for write permissions with the following options:
  * (A)llow
  * (D)eny
  * (I)gnore
  * (G)lob
  * Glob with (E)xtension
  * (N)ew
  * Audi(t)
  * (O)wner permissions off
  * Abo(r)t
  * (F)inish
* We can press (A)llow and save

This gives the executable write access to the `/home/some/specific/path/test.txt` file.

To edit the profile:
* Open profile in Vim: `sudo vim /etc/apparmor.d/home.some.specific.path.a.out`
* Edit the permission line to use glob syntax: `owner /home/*/Code/general-linux-practice/AppArmor/examples/* w,`
* Disable and re-enable the profile: `sudo aa-disable a.out`, `sudo aa-enforce a.out`

Now we can edit files in `examles/*`

## Example 2: Bash Script with Network Access

Bash scripts are actually a little more complicated than a binary.

This `downloadscript.sh` script downloads the Github logo:
```bash
#!/bin/bash

wget -P ~/Downloads https://github.com/favicon.ico
ls -l ~/Downloads
```

Generate a profile: `sudo aa-genprof downloadscript.sh`

Run the script: `./downloadscript.sh`

Scan events: `S` and get options:
* (I)nherit     (Inherits permissions from bash)
* (C)hild       (Inherits permissions from wget)
* (P)rofile     (?)
* (N)amed       (Inherits permissions from a named profile)
* (U)nconfined
* (X) ix On
* (D)eny
* Abo(r)t
* (F)inish

To edit the profile:
* Open `sudo vim /etc/apparmor.d/home.mark.Code.general-linux-practice.AppArmor.examples.downloadscript.sh`


