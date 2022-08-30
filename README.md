# New receiver type plugins

## lut
Takes arguments: 

"gainFile": Path to file containing gains to use in look up table. Gain file consists of nKernels, nDirections then the az and inc and gains for each channel.

"az_spcaing" and "el_spacing": the spacing between entries in the regular dense look up table in degrees. This look up table has entries that point to the nearest entry from the gain file.

"use3D": if = 1 az and el spacing used to make LUT, if = 0 the dense LUT only uses horizontal plane. 

Uses lut.h and lut.cc files found in libtascar folder

## nspn and vbapn
Versions of plugins whiuch only applies gains for active speakers. vbapn also uses 1-norm.

## nsplut and vbaplut
Versions of nspn and vbapn which use 720 entry LUTs on the horizontal plane  to find the active speakers so that computations don't scale  as much with the number of speakers.

## hoa2d_enc
HOA encoder for 2D only so outputs less channels, uses modified hoa.h file

## hoa2d_hybrid and hoa2dhybridv
Takes in attribute "Diviser" which is equal to the number of VSPKS positioned regularly on horizontal plane. The sources are first encoded onto virtual speaker channels using nearest speaker of vbap, and then vspk channels are encoded into hoa.

## null plugins
  Plugins were created with no real-time processing (an empty addpointsource function)

  hoa2d_hybrid nsplut vbaplut lut
  lutnull nsplutnull nspnnull vbaplutnull vbapnnull
  hoa2d_hybridnull hoa2dhybridvnull hoa3d_encnull hoa2d_encnull

# Toolbox for Acoustic Scene Creation and Rendering (TASCAR)

TASCAR is a collection of tools for creating spatially dynamic
acoustic scenes in different render formats, e.g. higher order
Ambisonics or VBAP. The toolbox has been developed for applications in
the context of hearing research and hearing aid evaluation.

For installation of binary packages, please see
[install.tascar.org](http://install.tascar.org/)

## References:

Grimm, Giso; Luberadzka, Joanna; Hohmann, Volker. A Toolbox for
Rendering Virtual Acoustic Environments in the Context of
Audiology. Acta Acustica united with Acustica, Volume 105, Number 3,
May/June 2019, pp. 566-578(13),
[doi:10.3813/AAA.919337](https://doi.org/10.3813/AAA.919337)


Grimm, G.; Luberadzka, J.; Herzke, T.; Hohmann, V. (2015): Toolbox for
acoustic scene creation and rendering (TASCAR) - Render methods and
research applications. in: Proceedings of the Linux Audio Conference,
Mainz, 2015 [paper](http://lac.linuxaudio.org/2015/papers/11.pdf)


Grimm, G.; Hohmann, V. (2014): Dynamic spatial acoustic scenarios in
multichannel loudspeaker systems for hearing aid evaluations. in:
Proc. of the 17th annual meeting of the Deutsche Gesellschaft fuer
Audiologie, Oldenburg, 2014. [conferece
proceedings](http://www.uzh.ch/orl/dga-ev/publikationen/tagungsbaende/tagungsbaende.html)


Grimm, G., & Herzke, T. (2012). A framework for dynamic spatial
acoustic scene generation with Ambisonics in low delay realtime. In
F. Neumann (Ed.), Proceedings of the Linux Audio Conference. Stanford,
CA, USA: Center for Computer Research in Music and Acoustics, Stanford
University. [paper](http://lac.linuxaudio.org/2012/papers/14.pdf)


## Main author:

Giso Grimm

g.grimm@uni-oldenburg.de


## Testing:

C++ unit tests (gtest):

````
make unit-tests
````

Reproducibility test:

````
make test
````

Measure test coverage:

````
make clean cleancov
make allwithcov
make coverage
````

