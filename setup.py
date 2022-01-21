from distutils.core import setup, Extension
import os

# change compiler to gcc
os.environ['CC'] = 'gcc'

src_dir = 'src'
ext_modules = [Extension('FastLine',
                         [src_dir + '/FastLine.cpp'],
                         language='c++',
                         depends=[src_dir + '/Line.h'],
                        #  #  lib dirj
                        #  library_dirs=[
                        #      'C:/Users/aliza/AppData/Local/Programs/Python/Python37/libs/'],
                         ), ]

setup(name='FastLine',
      version='1.0',
      ext_modules=ext_modules,
      author='M.Ali Zarrinzade',
      author_email="ali.zarrinzadeh@gmail.com",
      description="FastLine",
      long_description="FastLine is module that provides line operations implemented in C++",
      license="MIT",
      classifiers=[
            'Development Status :: 5 - Production/Stable',
            'Intended Audience :: Developers',
            'Intended Audience :: Science/Research',
            'Programming Language :: Python :: 3',
      ]
      )
