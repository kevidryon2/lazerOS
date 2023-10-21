v=$(echo $(( `date +"%U"` - 42)).`date +"%u%H"`.$(( `date +"%M"` / 10 ))_$1)
git add *
git commit -m "$v"