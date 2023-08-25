The original MicroEMACS
=======================

MicroEMACS is a tool for creating and changing documents, programs, and
other text files.  It is both relatively easy for the novice to use, but
also very powerful in the hands of an expert.  MicroEMACS can be
extensively customized for the needs of the individual user.

MicroEMACS allows several files to be edited at the same time.  The
screen can be split into different windows and screens, and text may be
moved freely from one window on any screen to the next.  Depending on the
type of file being edited, MicroEMACS can change how it behaves to make
editing simple.  Editing standard text files, program files and word
processing documents are all possible at the same time.


This Variant
------------

This variant's whole purpose is to build on v7 Unix on the PDP-11,
because I like v7 a lot, but don't like that it doesn't have a screen
editor.  Although I've gotten `s` to build on v7, I'd really rather have
an emacs.

So what I did was clone https://github.com/troglobit/MicroEMACS and then
check out the initial commit, using the reasoning that enhancements cost
space, which I don't have on a PDP-11, and portability features and
autotools weren't going to help me any, since I was building on
basically a 1979 system.

Once I'd done that it was just a matter of fiddling with it a little;
the only thing that really needed doing was to find the exported symbols
(in this case, just function names) and make them unique in the first
seven characters.  Hey, that's one more character than you get on
TOPS-20.

### Getting the sources onto a v7 system

Probably you're running on v7 on simh; possibly v7 on real iron.

The first thing you will need to do is construct a tarball.  Clone this
repository.

Then change to the top level directory (where this `README.md` file is)
and run (assuming GNU tar or MacOS bsd tar) `tar --format=v7 -cf
uemacs.tar *`.  (`--format=v7` is needed so you can unpack it on the
other end).  

If you've got UUCP reliably running, you can just send the tarball over
to your v7 system with it.  But let's assume you don't, because setting
it up can be tricky.

Now uuencode the tarball with `uuencode uemacs.tar uemacs.tar >
uemacs.uue` (the v7 filesystem won't let you call it `uemacs.tar.uue` on
the other end).

Now comes the slightly tricky part: you're going to need uudecode on the
v7 system.  I think you should probably just go to
https://github.com/athornton/uucode-v7 and get `uudecode.c`.

On the v7 system, make sure that characters-you-might-find in a C
program, or in a uuencoded stream, aren't going to mess you up (in
particular, `#` may well be your erase character).  I use the following
invocation: `stty 9600 erase '^h' kill '^u' cr0 nl0` (I also keep that
in my `.profile`.)

Now copy the contents of `uemacs.uue` into your paste buffer, and then,
assuming your terminal emulator has a "paste slowly" feature (iTerm2 for
MacOS certainly does, and is what I use), use cat to paste that into a
file named `uudecode.c` on the v7 side (after pasting, add a newline if
the paste didn't, and then Ctrl-D to close the file).  Then you can `cc
-o uudecode uudecode.c` and copy `uudecode` into somewhere on your
path.

Then you're going to do something a little time-consuming, but
conceptually easy: slow-paste `uemacs.uue` into a file of that name on
the v7 system, using `cat`, just like you did for the `uudecode` source
(preferably in an empty directory).  Once it's there, uudecode and untar
it.

I will be the first to admit that slow-pasting uuencoded tarballs is not
an elegant way of getting files into a v7 system, but it's a very
effective one.

### Building

I mean, I *guess* I could create a v7-appropriate Makefile, but
`cc -O -DV7=1 -o emacs *.c` works just fine.  I suspect the `DV7` is a
no-op.

### Running

This emacs is hardcoded for VT100, and has no concept of an abstraction
library like curses, which is good since there is no v7 curses.

You will need to run the following before running emacs (putting it in
your `.profile` may be a good idea):
```
TERM=vt100
export TERM
```
When you run it you will notice the arrow keys don't work, and most
likely neither does your meta key.  There might be some way to fix that
in an rc file, but C-b, C-f, C-p, and C-n all work, and
press-and-release ESC serves as Meta.

The rest of this README is imported from the upstream MicroEMACS
repository.

History
-------

The development of MicroEMACS by Mr Conroy stopped fairly early on but
Steve Wilhite and George Jones made fixes in the latter half of the 80s
when porting it to the Amiga and released their changes back to the
public domain.  Brian Straight wrote a MicroEMACS manual in 1987, and we
ended up with a collection of patches in 1988 bundled with Straight's
manual that was referred to as "Version 3".  That same year Daniel
M. Lawrence (1958 - 2010) started issuing patches that he named as 3.x
branches.


Origin & References
-------------------

The original MicroEMACS by Dave Conroy, first released in Nov. 1985.
The last public domain release was version 3.6, by Daniel Lawrence.
