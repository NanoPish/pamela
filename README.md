# PAMELA PAM module (alpha 0.1, unstable)

PAMELA is a PAM module that can creates an encrypted container for each user of the system.

PAMELA was only tested on Debian.

The created container, the volume and the key are in the home of each user.

## REQUIREMENTS

* pam (pam service)
* libpam0g-dev (pam devel)
* check (unit test framework)

## INSTALLATION

* Only a super user or a sudoer can install PAMELA

> make
> make install
> make check
> make test
> make clean

## UNINSTALLATION

> make uninstall

