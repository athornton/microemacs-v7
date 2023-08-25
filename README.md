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

### Building

I mean, I *guess* I could create a v7-appropriate Makefile, but
`cc -O -DV7=1 -o emacs *.c` works just fine.

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
