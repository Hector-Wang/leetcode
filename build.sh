if [ $# -lt 1 ]
then
    echo "usage: sh build.sh filename"
    exit 0
fi

filename=$1
gcc -fsanitize=address -O1 -fno-omit-frame-pointer -g $filename