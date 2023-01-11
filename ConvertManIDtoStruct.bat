SETLOCAL ENABLEDELAYEDEXPANSION

set /a counter=-2
@for /F "tokens=2,3 delims=," %%i in (manid.csv) do @(
	@set /a counter=!counter!+1
	@echo TEDSManIDArray[!counter!].ManID = %%i;
	@echo TEDSManIDArray[!counter!].ManName = "%%j";
	)