ENV ?= arduino

all: compiledb upload monitor

upload:
	pio run -e $(ENV) -t upload

monitor:
	pio device monitor

compiledb:
	pio run -e $(ENV) -t compiledb
