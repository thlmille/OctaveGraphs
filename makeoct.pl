#!/usr/bin/perl
my $target = $ARGV[0];
open (THEFILE, '>temp');
print THEFILE "mkoctfile $target Graph.cc badargs.cc";
system('octave <temp');
system('rm temp');
