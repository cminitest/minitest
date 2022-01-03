#!/bin/sh

project_chsum=""

watch_project() {
  chsum2=`find . -type f \( -name "*.h" -o -name "*.c" -o -name "*.in" \) -mtime -5 -exec md5 {} \;`
  if [[ $project_chsum != $chsum2 ]] ; then
    make clean
    autoconf
    ./configure
    make uninstall ; make ; ./bin/testsuite
    echo $?
    project_chsum=$chsum2
  fi
}

while [[ true ]]
do
  watch_project
  sleep 5
done