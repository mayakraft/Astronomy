![transform](https://raw.githubusercontent.com/robbykraft/Astronomy/master/bin/transformation.png)

# try it

type `make` then `make run`

```
 LONGITUDE             TIME               ORBIT          ROTATION

Earth    0°      July 22, 2016 (0:00)    -60°   SIDE:300.18   APPR:-0.00085
Earth    0°    August 22, 2016 (0:00)    -30°   SIDE:330.73   APPR:0.00075
Earth    0° September 22, 2016 (0:00)      0°   SIDE:  1.29   APPR:-0.00471
Earth    0°   October 22, 2016 (0:00)     28°   SIDE: 30.86   APPR:-0.00043
```

# J2000.h

convert human readable dates into J2000 format 

# sidereal.h

input: `time, longitude on Earth`

output: `mean sidereal time and apparent sidereal time`

# kepler.h

Keplerian Elements for Approximate Positions of the Major Planets

input: `date`

output: `positions (X,Y,Z) for each planet`

units: `astronomical units, origin at the sun, X axis aligned with the equinox`

[NASA JPL (sec 8.10)](http://iau-comm4.jpl.nasa.gov/XSChap8.pdf)

[positions valid for 1800 AD - 2050 AD](http://ssd.jpl.nasa.gov/?planet_pos) 