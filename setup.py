from distutils.core import setup, Extension
import os

# change compiler to gcc
os.environ['CC'] = 'gcc'

src_dir = 'src'
ext_modules = [Extension('FastLine',
                         [src_dir + '/FastLine.cpp'],
                         language='c++',
                         ), ]

setup(name='FastLine',
      version='1.0',
      ext_modules=ext_modules,
      author='M.Ali Zarrinzade',
      author_email="ali.zarrinzadeh@gmail.com",
      description="FastLine",
      long_description=open("README.md").read(),
      long_description_content_type="text/markdown",
      license="MIT",
      classifiers=[
          'Development Status :: 5 - Production/Stable',
          'Intended Audience :: Developers',
          'Intended Audience :: Science/Research',
          'Programming Language :: Python :: 3',
      ],
      url="https://github.com/MrGolden1/FastLine",
      project_urls={
          "Bug Tracker": "https://github.com/MrGolden1/FastLine/issues",
      },
      )
