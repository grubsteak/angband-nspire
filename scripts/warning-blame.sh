#!/bin/sh

# Copyright 2007 Vincent Sanders <vince@debian.org>
# All rights reserved.

# Taken from the NetSurf SVN repository:
# http://source.netsurf-browser.org/trunk/netsurf/utils/warning-blame.sh

# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. Neither the name of the Author nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.

# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.


# where to store the processed list of warnings
WARNING_LIST=/tmp/warning-list

if [ $# != 1 ]; then
	echo "Syntax: $0 <warning-file>"
	exit 1
fi

if [ -f $1 ]; then
	cp $1 ${WARNING_LIST}
else
	echo "Need a valid warning file"
	exit 1
fi

for blamefile in $(cat ${WARNING_LIST} | cut -f 1 -d ':'  | sort | uniq ); do
  if [ -f ${blamefile} ]; then
    svn blame ${blamefile} >/tmp/blame

    cat ${WARNING_LIST} | grep "^${blamefile}" >/tmp/blame-warnings

    while read warning; do
      echo ${warning}

      lineno=$(echo ${warning} | cut -f 2 -d ':' ; )

      cat /tmp/blame | head -n ${lineno} | tail -n 1

    done < /tmp/blame-warnings
    rm /tmp/blame-warnings
  else
    echo "Unable to find ${blamefile}"
  fi
done 
