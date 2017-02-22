#!/bin/bash


# i shift all the number data by 5 bits

#if data doesnt exist, generate 10 random numbers/guesses
if [ ! -f ./Data.pg ]; then 
	echo "tries" >> Data.pg 
	echo "$((2 << 5))" >> Data.pg #number of tries 
	echo "guesses" >> Data.pg
	echo "generated" >> Data.pg
	counter=1
	while [ $counter -le 10 ]; do
		rnd=$((RANDOM % 50+ 1))
		(( rnd <<=5 ))
		echo "$rnd" >> Data.pg # r to indicate its generated
		((counter++))
	done
fi

#gameplay, 3 guesses
i=1

while [ $i -le 3 ]; do
	
	input="Data.pg"

	#reset data for the game
	avgGuesses=0
	totalTries=0
	numTries=0

	while read -r line
	do
		#decide what data is being read
		if [[ $line == tries ]]; then
			readTries=true
			continue
		elif [[ $line == guesses ]]; then
			readTries=false
			continue
		fi

		#incrementing depending on data read
		if [[ $readTries == true ]]; then
			(( line >>= 5))
			((totalTries+=line))
			((numTries++))
		else
			(( line >>=5 ))
			((avgGuesses+=line))
		fi	
	done < "$input"

	#calculating the new guesses and win condition
	((avgGuesses /= 10))
	((avgGuesses *= 2/3))
	lo=$((avgGuesses - avgGuesses/10))
	hi=$((avgGuesses + avgGuesses/10))


	avgTries=$((totalTries / numTries))
	#first run prompt
	if [ $i -eq 1 ]; then
		echo "Guess Number? "
	fi
	read guess

	((guess <<= 5))
	#insert guess into data
	sed -i "" "/guesses/a\ 
		$guess
		" $input
	#delete oldest guess which is at the bottom
	sed -i -n -e :a -e '1,1!{P;N;D;};N;ba' $input

	#win condition
	if [ $guess -le $hi ] && [ $guess -ge $lo ]; then
		if [ $i -eq 1 ]; then
			echo "Well Done. You took 1 try to guess. Average tries is $avgTries"
		else
			echo "Well Done. You took $i tries to guess. Average tries is $avgTries"
		fi
		#insert number of tries into data

		n_tries = $(( i<<5 ))
		sed -i "" "/tries/a\ 
		$n_tries
		" $input
		exit

	else
		echo "Incorrect guess. Try again."
	fi

	((i++))
done

#you failed to guess
echo "You were not able to guess."
exit