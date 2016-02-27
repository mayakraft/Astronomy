# kepler.c

Keplerian Elements for Approximate Positions of the Major Planets

**input:** date

**output:** positions (X,Y,Z) in space for each planet, measured in astronomical units, origin at the sun, X axis aligned with the equinox

positions valid for 1800 AD - 2050 AD


[NASA JPL (sec 8.10)](http://iau-comm4.jpl.nasa.gov/XSChap8.pdf)

[information on margin of error](http://ssd.jpl.nasa.gov/?planet_pos) 

# stargaze.c

**stargaze.c in development**

these are the missing set of functions required to build stargazing apps on mobile devices

![transform](https://raw.github.com/robbykraft/Stargaze/master/bin/transformation.png)

**input:** your location on Earth, time, and day of year

**output:** a rotation matrix that is your difference from the ecliptic plane (+Z orthogonal, +X RA0), and your compass orientation (+Z orthogonal to ground, +X compass north/true north)

# sidereal.c

**input:** time, location on earth

**output:** mean sidereal time and apparent sidereal time

# J2000.c

convert dates into J2000 format, units are in days

`0.0` in J2000 is `January 1st, 2000`