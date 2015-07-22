'''
Input parameters for W-phase inversion
'''

############################################################################
#
#                  W phase source inversion package                 
#                               -------------
#
#        Main authors: Zacharie Duputel, Luis Rivera and Hiroo Kanamori
#                      
# (c) California Institute of Technology and Universite de Strasbourg / CNRS 
#                                  April 2013
#
#    Neither the name of the California Institute of Technology (Caltech) 
#    nor the names of its contributors may be used to endorse or promote 
#    products derived from this software without specific prior written 
#    permission
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
############################################################################

import os 

# Time-shift grid-search parameters
TS_OFILE = 'grid_search_ts_out'

# Centroid Lat/Lon grid-search parameters
XY_OFILE = 'grid_search_xy_out'

# Centroid Depth grid-search parameters
XYZ_OFILE = 'grid_search_xyz_out'

# Filenames
IMASTER         = 'i_master'      # IMASTER FILENAME
O_WPINVERSION   = 'o_wpinversion' # o_wpinversion filename
LOGDIR          = 'LOG'

# Traces plot parameters
TRACES_FIGSIZE  = [11.69,8.270]

# cwp plot parameters
CWP_FIGSIZE   = [11.69,8.27]

TRACES_PLOTPARAMS = {'backend': 'pdf', 'axes.labelsize': 10,
                     'font.size': 10,
                     'xtick.labelsize': 10,
                     'ytick.labelsize': 10,
                     'legend.fontsize': 10,
                     'lines.markersize': 6,
                     'font.size': 10,
                     'savefig.dpi': 200,
                     'keymap.all_axes': 'a',
                     'keymap.back': ['left', 'c', 'backspace'],
                     'keymap.forward': ['right', 'v'],
                     'keymap.fullscreen': 'f',
                     'keymap.grid': 'g',
                     'keymap.home': ['h', 'r', 'home'],
                     'keymap.pan': 'p',
                     'keymap.save': 's',
                     'keymap.xscale': ['k', 'L'],
                     'keymap.yscale': 'l',
                     'keymap.zoom': 'o',                  
                     'path.snap': True,
                     'savefig.format': 'pdf',
                     'pdf.compression': 9,
                     'figure.figsize': TRACES_FIGSIZE}


# W-phase home directory
WPHOME = os.path.expandvars('$WPHASE_HOME')
print('WPHASE_HOME is %s'%(WPHOME))
if WPHOME[-1] != '/':
    WPHOME += '/'

GF_PATH = os.path.expandvars('$GF_PATH')
print('GF_PATH is %s'%(GF_PATH))

# Path to binaries
BIN = WPHOME+'bin/'

WPINV_XY = BIN+'wpinversion_gs -imas i_master -ifil '+O_WPINVERSION
SYNTHS   = WPHOME+'bin/synth_v6'

