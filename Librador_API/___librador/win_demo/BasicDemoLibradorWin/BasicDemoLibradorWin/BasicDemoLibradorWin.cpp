#include <iostream>
#include "librador.h"

static constexpr double kPowerSupplyVoltage = 7.3f;
static constexpr double kSignalGeneratorFrequencyHz = 912.f;
static constexpr double kSignalGeneratorAmplitudeV = 1.8f;
static constexpr double kSignalGeneratorOffsetV = 0.7f;

int main()
{
	printf("Starting the demo with debugging disabled...\nAdd LIBRADOR_ENABLE_LOGGING to your defines to add debug output.\n");

	// Initialise Librador
	int error = librador_init();
	if (error)
	{
		printf("librador_init FAILED with error code %d\tExiting...", error);
		return error;
	}

	// Initialise the USB
	error = librador_setup_usb();
	if (error)
	{
		printf("librador_setup_usb FAILED with error code %d\tExiting...", error);
		return error;
	}
	printf("Device Connected Successfully!\n");

	// Print firmware info
	uint16_t deviceVersion = librador_get_device_firmware_version();
	uint8_t deviceVariant = librador_get_device_firmware_variant();
	printf("deviceVersion=%hu, deviceVariant=%hhu\n", deviceVersion, deviceVariant);

	// Set the power supply voltage
	error = librador_set_power_supply_voltage(kPowerSupplyVoltage);
	if (error)
	{
		printf("librador_set_power_supply_voltage FAILED with error code %d\tExiting...", error);
		return error;
	}
	printf("Successfully set power supply voltage to %.2fV\n", kPowerSupplyVoltage);

	// Put different waveforms on the two signal generator channels
	error = librador_send_sin_wave(1, kSignalGeneratorFrequencyHz, kSignalGeneratorAmplitudeV, kSignalGeneratorOffsetV);
	if (error)
	{
		printf("librador_send_sin_wave FAILED with error code %d\tExiting...",
		    error);
		return error;
	}
	printf("Successfully put %.2fHz sine wave on channel 1\n", kSignalGeneratorFrequencyHz);

	error = librador_send_triangle_wave(2, kSignalGeneratorFrequencyHz, kSignalGeneratorAmplitudeV, kSignalGeneratorOffsetV);
	if (error)
	{
		printf("librador_send_sin_wave FAILED with error code %d\tExiting...", error);
		return error;
	}
	printf("Successfully put %.2fHz triangle wave on channel 2\n", kSignalGeneratorFrequencyHz);

	// Cleanup and exit
	error = librador_exit();
	if (error)
	{
		printf("librador_exit FAILED with error code %d\tExiting...", error);
		return error;
	}
	printf("librador_exit executed successfully\n");
	
	return 0;
}