#
# The Python Imaging Library.
# $Id$
#
# package placeholder
#
# Copyright (c) 1999 by Secret Labs AB.
#
# See the README file for information on usage and redistribution.
#

# ;-)

from . import version

VERSION = '1.1.7'  # PIL Version
PILLOW_VERSION =  version.__version__

__version__ = PILLOW_VERSION

_plugins = ['BmpImagePlugin',
            'BufrStubImagePlugin',
            'CurImagePlugin',
            'DcxImagePlugin',
            'DdsImagePlugin',
            'EpsImagePlugin',
            'FitsStubImagePlugin',
            'FliImagePlugin',
            'FpxImagePlugin',
            'FtexImagePlugin',
            'GbrImagePlugin',
            'GifImagePlugin',
            'GribStubImagePlugin',
            'Hdf5StubImagePlugin',
            'IcnsImagePlugin',
            'IcoImagePlugin',
            'ImImagePlugin',
            'ImtImagePlugin',
            'IptcImagePlugin',
            'JpegImagePlugin',
            'Jpeg2KImagePlugin',
            'McIdasImagePlugin',
            'MicImagePlugin',
            'MpegImagePlugin',
            'MpoImagePlugin',
            'MspImagePlugin',
            'PalmImagePlugin',
            'PcdImagePlugin',
            'PcxImagePlugin',
            'PdfImagePlugin',
            'PixarImagePlugin',
            'PngImagePlugin',
            'PpmImagePlugin',
            'PsdImagePlugin',
            'SgiImagePlugin',
            'SpiderImagePlugin',
            'SunImagePlugin',
            'TgaImagePlugin',
            'TiffImagePlugin',
            'WebPImagePlugin',
            'WmfImagePlugin',
            'XbmImagePlugin',
            'XpmImagePlugin',
            'XVThumbImagePlugin']


from ._imagingbuilds import get_available_builds


_current_build = get_available_builds()[0]


def get_build():
    return _current_build


def set_build(build):
    global _current_build
    available_builds = get_available_builds()
    if build not in available_builds:
        raise ValueError("build %s not available; "
                         "following is the list of available builds: \n%s" %
                         (build, '\n'.join(available_builds)))
    _current_build = build

    from .Image import _import_core
    _import_core()
