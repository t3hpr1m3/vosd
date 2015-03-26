#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([vosd], [0.1.0], [vmizzle@gmail.com])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.

dnl Check for alsa
PKG_CHECK_MODULES(ALSA, alsa >= 1.0.0)
AC_SUBST(ALSA_CFLAGS)
AC_SUBST(ALSA_LIBS)

dnl Check for xosd
AM_PATH_LIBXOSD

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile
					src/Makefile
					src/alsa/Makefile])
AC_OUTPUT
