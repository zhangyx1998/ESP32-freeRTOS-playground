all: compiledb upload monitor

upload:
	pio run -t upload

monitor:
	pio device monitor

compiledb:
	pio run -t compiledb
