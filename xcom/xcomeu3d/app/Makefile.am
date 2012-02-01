
SUBDIRS = src

EXTRA_DIST = AUTHORS COPYING ChangeLog INSTALL README TODO

dist-hook:
	rm -rf `find $(distdir) -name CVS -type d`

# not a GNU package. You can remove this line, if
# have all needed files, that a GNU package needs
AUTOMAKE_OPTIONS = foreign 1.4


