
Debian
====================
This directory contains files used to package vaperscoind/vaperscoin-qt
for Debian-based Linux systems. If you compile vaperscoind/vaperscoin-qt yourself, there are some useful files here.

## vaperscoin: URI support ##


vaperscoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install vaperscoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your vaperscoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/vaperscoin128.png` to `/usr/share/pixmaps`

vaperscoin-qt.protocol (KDE)

