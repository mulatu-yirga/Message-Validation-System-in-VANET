all: trace sim

trace:
	sumo -c sim.sumocfg --fcd-output sumoTrace.xml
	traceExporter.py --fcd-input sumoTrace.xml --ns2mobility-output ns2mobility.tcl

sim:
	sumo-gui sim.sumocfg

clean:
	rm -f sumoTrace.xml ns2mobility.tcl
