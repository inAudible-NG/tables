## NOTE (Licensing)

Commercial usage of this project requires a license from the author(s) of
this project. Contact us for details.

Note: The licensing terms of this project were changed due to commercial abuse
from OpenAudible (http://openaudible.org/) and other projects.

## About

Plugin for [RainbowCrack](http://project-rainbowcrack.com/) to recover your own
Audible activation data (activation_bytes) in an offline manner.

You need to recover or retrieve your "activation_bytes" only once. This single
"activation_bytes" value will work for all your .aax files.

## Donations

Donations are gladly accepted. Please send BTC to `1FDFp8kWjnUCGTLw1SVkim6kRnYDge2vYh`
to support the development, and maintenance of this project. Thank you!

## Note

Git clone this repository on your machine. This repository has the required
rainbow tables `(*.rtc files)` and RainbowCrack binaries.

```
git clone https://github.com/inAudible-NG/tables.git
```

## Usage on Linux

FFmpeg 2.8.1+ is required. Use Wine with the included (in `run` folder) Windows
binaries in case these Linux executables do not run on your distribution.

##### Extract SHA1 checksum from the .aax file

```
$ ffprobe test.aax  # extract SHA1 checksum
...
[mov,mp4,m4a,3gp,3g2,mj2 @ 0x1dde580] [aax] file checksum == 999a6ab8...
[mov,mp4,m4a,3gp,3g2,mj2 @ 0x1dde580] [aax] activation_bytes option is missing!
```

##### Recover "activation_bytes"

```
$ ./rcrack . -h 999a6ab8...
```

## Usage on Windows

Download FFmpeg from https://ffmpeg.zeranoe.com/builds/.

##### Extract SHA1 checksum from .aax file

```
C:\>ffprobe.exe sample.aax
ffprobe version N-79460-g21acc4d Copyright (c) 2007-2016 the FFmpeg developers
  built with gcc 5.3.0 (GCC)
...
[mov,mp4,m4a,3gp,3g2,mj2 @ 039aae60] [aax] file checksum == 999a6ab8...
[mov,mp4,m4a,3gp,3g2,mj2 @ 039aae60] [aax] activation_bytes option is missing!
```

##### Recover "activation_bytes"

```
C:\tables>run\rcrack.exe . -h 999a6ab8...
statistics
-------------------------------------------------------
plaintext found:                              1 of 1
total time:                                   13.98 s
...
result
-------------------------------------------------------
999a6ab8...                               xyz   hex:CAFED00D
```

"activation_bytes" is CAFED00D here.

## References

See http://project-rainbowcrack.com/alglib.htm for details.
