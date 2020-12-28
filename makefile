ZIP		=RCOM_T2G4_Proj2

all:

doc/report/report.pdf: FORCE
	make -C doc/report report.pdf

$(ZIP): doc/report/report.pdf
	mkdir -p $(ZIP)
	mkdir -p $(ZIP)/download
	mkdir -p $(ZIP)/part2
	cp doc/report/report.pdf $(ZIP)
	cp -r download/* $(ZIP)/download/
	cp -r part2/* $(ZIP)/part2/
	rm -rf $(ZIP)/config
	rm -f $(ZIP)/*.md
	rm -f $(ZIP)/*/*.md

zip: $(ZIP).zip

$(ZIP).zip: $(ZIP)
	cd $(ZIP) && zip -r ../$(ZIP).zip .
	rm -rf $(ZIP)

zipsmall: $(ZIP)_small.zip

$(ZIP)_small.zip: $(ZIP)
	rm -f $(ZIP)/exp6/6-5-tux32.pcapng $(ZIP)/exp6/6-5-tux33.pcapng
	cd $(ZIP) && zip -r ../$(ZIP)_small.zip .
	rm -rf $(ZIP)

FORCE:
