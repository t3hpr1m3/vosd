/*
 * Copyright (c) 2015 Josh Williams <theprime@codingprime.com>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the COPYING file for details.
 */
#include <unistd.h>
#include <xosd.h>

#include "alsa/alsa.h"
#include "log.h"

struct Options {
	int HwId;
	std::string Mixer;
	std::string Action;
};

void commandDefaults(Options& pOptions) {
	pOptions.HwId = 0;
	pOptions.Mixer = "unknown";
	pOptions.Action = "unknown";
}

bool parseCommandLine(int pCount, char* pArgs[], Options& pOptions) {
	int c, vIndex;

	opterr = 0;

	while ((c = getopt(pCount, pArgs, "c:m:")) != -1) {
		switch (c) {
			case 'c':
				pOptions.HwId = atoi(optarg);
				break;
			case 'm':
				pOptions.Mixer = optarg;
				break;

		}
	}

	vIndex = optind;
	if (vIndex < pCount) {
		pOptions.Action = pArgs[vIndex];
	}

	return true;
}

int main(int argc, char *argv[]) {
	Options vOptions;
	commandDefaults(vOptions);

	if (parseCommandLine(argc, argv, vOptions)) {
		VOsd::Alsa* alsa = new VOsd::Alsa();

		if (alsa->Init()) {
			VOsd::AlsaCard* vCard = alsa->Card(vOptions.HwId);
			if (vCard != NULL) {
				VOsd::AlsaMixer* vMixer = vCard->Mixer(vOptions.Mixer);
				if (vMixer != NULL) {
					VOsd::Log().Debug() << "Found Mixer!";
					VOsd::Log().Debug() << "  " << vCard->Name();
					VOsd::Log().Debug() << "    " << vMixer->Name();
					long vCurrent;

					if (vOptions.Action.compare("up") == 0) {
						vMixer->VolumeChange(VOsd::AlsaMixer::MixerLeft, 1);
						vMixer->VolumeChange(VOsd::AlsaMixer::MixerRight, 1);
					} else if (vOptions.Action.compare("down") == 0) {
						vMixer->VolumeChange(VOsd::AlsaMixer::MixerLeft, -1);
						vMixer->VolumeChange(VOsd::AlsaMixer::MixerRight, -1);
					} else if (vOptions.Action.compare("mute") == 0) {
						vMixer->ToggleMute();
					}

					xosd* vOsd;
					vOsd = xosd_create(2);
					if (vOsd == NULL) {
						VOsd::Log().Error() << "Could not initialize OSD.";
					} else {
						vMixer->Volume(VOsd::AlsaMixer::MixerLeft, &vCurrent);
						xosd_set_font(vOsd, "-*-terminus-medium-*-normal-*-32-*-*-*-*-*-*-*");
						xosd_set_colour(vOsd, "#666666");
						xosd_set_shadow_offset(vOsd, 2);
						xosd_set_pos(vOsd, XOSD_middle);
						xosd_set_align(vOsd, XOSD_center);
						xosd_set_bar_length(vOsd, 100);
						xosd_set_timeout(vOsd, 2);
						xosd_display(vOsd, 0, XOSD_percentage, vCurrent);
						xosd_wait_until_no_display(vOsd);
						xosd_destroy(vOsd);
					}
				}
			}
		} else {
			VOsd::Log().Debug() << "Unable to initialize.";
		}

		delete alsa;
		return 0;
	} else {
		VOsd::Log().Error() << "Unable to parse command line.";
	}
}

