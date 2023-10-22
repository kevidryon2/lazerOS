if test -z $1; then
	v=$(echo $(( `date +"%U"` - 42)).`date +"%u%H"`.$(( `date +"%M"` / 10 )))
else
	v=$(echo $(( `date +"%U"` - 42)).`date +"%u%H"`.$(( [ `date +"%M"` ] / 10 ))_$1)
fi

git add *
git commit -m "$v"