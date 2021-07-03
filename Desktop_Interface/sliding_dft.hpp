/**
Sliding discrete Fourier transform (C++)
====

This code efficiently computes discrete Fourier transforms (DFTs) from a
continuous sequence of input values. It is a recursive algorithm that updates
the DFT when each new time-domain measurement arrives, effectively applying a
sliding window over the last *N* samples. This implementation applies the
Hanning window in order to minimise spectral leakage.

The update step has computational complexity *O(N)*. If a new DFT is required
every *M* samples, and *M* < log2(*N*), then this approach is more efficient
that recalculating the DFT from scratch each time.

This is a header-only C++ library. Simply copy sliding_dft.hpp into your
project, and use it as follows:

	// Use double precision arithmetic and a 512-length DFT
	static SlidingDFT<double, 512> dft;
	// avoid allocating on the stack because the object is large

	// When a new time sample arrives, update the DFT with:
	dft.update(x);

	// After at least 512 samples have been processed:
	std::complex<double> DC_bin = dft.dft[0];

Your application should call update() as each time domain sample arrives. Output
data is an array of `std::complex` values in the `dft` field. The length of this
array is the length of the DFT.

The output data is not valid until at least *N* samples have been processed. You
can detect this using the `is_data_valid()` method, or by storing the return
value of the `update()` method.

This is a header-only C++ library. Simply copy sliding_dft.hpp into your
project. The included CMakeLists.txt is for building the testbench.

Implementation details
----

See references [1, 2] for an overview of sliding DFT algorithms. A damping
factor is used to improve stability in the face of numerical rounding errors. If
you experience stability issues, reduce `dft.damping_factor`. It should be
slightly less than one.

Windowing is done using a Hanning window, computed in the frequency domain [1].

[1] E. Jacobsen and R. Lyons, “The Sliding DFT,” IEEE Signal Process. Mag., vol. 20, no. 2, pp. 74–80, Mar. 2003.

[2] E. Jacobsen and R. Lyons, “An Update to the Sliding DFT,” IEEE Signal Process. Mag., vol. 21, no. 1, pp. 110-111, 2004.


MIT License
----

Copyright (c) 2016 Bronson Philippa

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#define _USE_MATH_DEFINES
#include <complex>
#include <math.h>

template <class NumberFormat, size_t DFT_Length>
class SlidingDFT
{
private:
	/// Are the frequency domain values valid? (i.e. have at elast DFT_Length data
	/// points been seen?)
	bool data_valid = false;

	/// Time domain samples are stored in this circular buffer.
	NumberFormat x[DFT_Length] = { 0 };

	/// Index of the next item in the buffer to be used. Equivalently, the number
	/// of samples that have been seen so far modulo DFT_Length.
	size_t x_index = 0;

	/// Twiddle factors for the update algorithm
	std::complex<NumberFormat> twiddle[DFT_Length];

	/// Frequency domain values (unwindowed!)
	std::complex<NumberFormat> S[DFT_Length];

public:
	/// Frequency domain values (windowed)
	std::complex<NumberFormat> dft[DFT_Length];

	/// A damping factor introduced into the recursive DFT algorithm to guarantee
	/// stability.
	NumberFormat damping_factor = std::nexttoward((NumberFormat)1, (NumberFormat)0);

	/// Constructor
	SlidingDFT()
	{
		const std::complex<NumberFormat> j(0.0, 1.0);
		const NumberFormat N = DFT_Length;

		// Compute the twiddle factors, and zero the x and S arrays
		for (size_t k = 0; k < DFT_Length; k++) {
			NumberFormat factor = (NumberFormat)(2.0 * M_PI) * k / N;
			this->twiddle[k] = std::exp(j * factor);
			this->S[k] = 0;
			this->x[k] = 0;
		}
	}

	/// Determine whether the output data is valid
	bool is_data_valid()
	{
		return this->data_valid;
	}

	/// Update the calculation with a new sample
	/// Returns true if the data are valid (because enough samples have been
	/// presented), or false if the data are invalid.
	bool update(NumberFormat new_x)
	{
		// Update the storage of the time domain values
		const NumberFormat old_x = this->x[this->x_index];
		this->x[this->x_index] = new_x;

		// Update the DFT
		const NumberFormat r = this->damping_factor;
		const NumberFormat r_to_N = pow(r, (NumberFormat)DFT_Length);
		for (size_t k = 0; k < DFT_Length; k++) {
			this->S[k] = this->twiddle[k] * (r * this->S[k] - r_to_N * old_x + new_x);
		}

		// Apply the Hanning window
		this->dft[0] = (NumberFormat)0.5*this->S[0] - (NumberFormat)0.25*(this->S[DFT_Length - 1] + this->S[1]);
		for (size_t k = 1; k < (DFT_Length - 1); k++) {
			this->dft[k] = (NumberFormat)0.5*this->S[k] - (NumberFormat)0.25*(this->S[k - 1] + this->S[k + 1]);
		}
		this->dft[DFT_Length - 1] = (NumberFormat)0.5*this->S[DFT_Length - 1] - (NumberFormat)0.25*(this->S[DFT_Length - 2] + this->S[0]);

		// Increment the counter
		this->x_index++;
		if (this->x_index >= DFT_Length) {
			this->data_valid = true;
			this->x_index = 0;
		}

		// Done.
		return this->data_valid;
	}
};
