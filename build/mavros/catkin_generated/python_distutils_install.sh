#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/johanna/catkin_mmc/src/mavros/mavros"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/johanna/catkin_mmc/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/johanna/catkin_mmc/install/lib/python2.7/dist-packages:/home/johanna/catkin_mmc/build/mavros/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/johanna/catkin_mmc/build/mavros" \
    "/usr/bin/python2" \
    "/home/johanna/catkin_mmc/src/mavros/mavros/setup.py" \
     \
    build --build-base "/home/johanna/catkin_mmc/build/mavros" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/johanna/catkin_mmc/install" --install-scripts="/home/johanna/catkin_mmc/install/bin"
