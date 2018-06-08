//##########################################################################
//#                                                                        #
//#                               CCLIB                                    #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU Library General Public License as       #
//#  published by the Free Software Foundation; version 2 or later of the  #
//#  License.                                                              #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#          COPYRIGHT: EDF R&D / TELECOM ParisTech (ENST-TSI)             #
//#                                                                        #
//##########################################################################

#ifndef CC_SCALAR_FIELD_HEADER
#define CC_SCALAR_FIELD_HEADER

//Local
#include "CCConst.h"
#include "CCCoreLib.h"

//System
#include <vector>

namespace CCLib
{

//! A simple scalar field (to be associated to a point cloud)
/** A mono-dimensionnal array of scalar values. It has also specific
	parameters for display purposes.

	Invalid values can be represented by NAN_VALUE.
**/
class CC_CORE_LIB_API ScalarField : public std::vector<ScalarType>
{
public:

	//! Default constructor
	/** [SHAREABLE] Call 'link' when associating this structure to an object.
		\param name scalar field name
	**/
	explicit ScalarField(const char* name = nullptr);

	//! Copy constructor
	/** \param sf scalar field to copy
		\warning May throw a std::bad_alloc exception
	**/
	ScalarField(const ScalarField& sf);

	//! Default destructor
	virtual ~ScalarField() {}

	//! Sets scalar field name
	void setName(const char* name);

	//! Returns scalar field name
	inline const char* getName() const { return m_name; }

	//! Returns the specific NaN value
	static inline ScalarType NaN() { return NAN_VALUE; }

	//! Computes the mean value (and optionally the variance value) of the scalar field
	/** \param mean a field to store the mean value
		\param variance if not void, the variance will be computed and stored here
	**/
	void computeMeanAndVariance(ScalarType &mean, ScalarType* variance = nullptr) const;

	//! Determines the min and max values
	void computeMinAndMax();

	//! Returns whether a scalar value is valid or not
	static inline bool ValidValue(ScalarType value) { return value == value; } //'value == value' fails for NaN values

	//! Sets the value as 'invalid' (i.e. NAN_VALUE)
	inline virtual void flagValueAsInvalid(size_t index) { at(index) = NaN(); }

	//! Returns the minimum value
	ScalarType min() const { return m_minVal; }
	//! Returns the maximum value
	ScalarType max() const { return m_maxVal; }

	//! Fills the array with a particular value
	void fill(ScalarType fillValue = 0) { std::fill(begin(), end(), fillValue); }

	//! Reserves memory (no exception thrown)
	bool reserveSafe(size_t count);
	//! Resizes memory (no exception thrown)
	bool resizeSafe(size_t count, bool initNewElements = false, ScalarType valueForNewElements = 0);

	//! Swaps two elements
	void swap(size_t i1, size_t i2);

	//Shortcuts (for backward compatibility)
	inline ScalarType& getValue(size_t index) { return at(index); }
	inline const ScalarType& getValue(size_t index) const { return at(index); }
	inline void setValue(size_t index, ScalarType value) { at(index) = value; }
	inline void addElement(ScalarType value) { push_back(value); }
	inline unsigned currentSize() const { return static_cast<unsigned>(size()); }

protected:

	//! Scalar field name
	char m_name[256];

	//! Minimum value
	ScalarType m_minVal;
	//! Maximum value
	ScalarType m_maxVal;
};

}

#endif //CC_SCALAR_FIELD_HEADER
