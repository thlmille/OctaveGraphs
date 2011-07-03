#!/usr/bin/perl

use warnings;
use strict;

my $dirname = "octfuncs";
opendir (DIR, $dirname) or die ("directory not found");
my @ccfiles = readdir DIR;
closedir DIR;

open (OCTREAD, '>temp');
foreach my $file (@ccfiles) {
    if (($file !~ m/.*~/) && ($file !~ m/^\./) && ($file !~ m/.*\.o/)) {
	if ((-f "Graph.o") && (-f "badargs.o")) {
	    print OCTREAD "mkoctfile octfuncs/$file Graph.o badargs.o\n";
	} else {
	    print OCTREAD "mkoctfile octfuncs/$file Graph.cc badargs.cc\n";
	}
    }
}
close(OCTREAD);
system ('octave <temp');
system ('rm temp');
