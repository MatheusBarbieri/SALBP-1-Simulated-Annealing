build:
		g++ -std=c++14 salbp1-simulated-annealing.cpp -o salbp1-sa

mertens:
	./salbp1-sa -c6 -v < "instances/MERTENS.IN2" 2>&1  | tee salbp1-sa-outputs/mertens_c6.txt
	./salbp1-sa -c15 -v < "instances/MERTENS.IN2" 2>&1 | tee salbp1-sa-outputs/mertens_c15.txt
	./salbp1-sa -c18 -v < "instances/MERTENS.IN2" 2>&1 | tee salbp1-sa-outputs/mertens_c18.txt

mitchell:
	./salbp1-sa -c14 -v < "instances/MITCHELL.IN2" 2>&1 | tee salbp1-sa-outputs/mitchell_c14.txt
	./salbp1-sa -c35 -v < "instances/MITCHELL.IN2" 2>&1 | tee salbp1-sa-outputs/mitchell_c35.txt
	./salbp1-sa -c26 -v < "instances/MITCHELL.IN2" 2>&1 | tee salbp1-sa-outputs/mitchell_c26.txt

wee-mag:
	./salbp1-sa -c56 -v < "instances/WEE-MAG.IN2" 2>&1 | tee salbp1-sa-outputs/wee-mag_c56.txt
	./salbp1-sa -c28 -v < "instances/WEE-MAG.IN2" 2>&1 | tee salbp1-sa-outputs/wee-mag_c28.txt
	./salbp1-sa -c36 -v < "instances/WEE-MAG.IN2" 2>&1 | tee salbp1-sa-outputs/wee-mag_c36.txt
	./salbp1-sa -c54 -v < "instances/WEE-MAG.IN2" 2>&1 | tee salbp1-sa-outputs/wee-mag_c54.txt

run: mertens mitchell wee-mag
