#pragma once
#include <iostream>

template <typename T>
class DynamicArray
{
public:

	// DynamicArray's constructor
	DynamicArray(int initialSize = 1)
	{
		m_Data = new T[initialSize];
		m_Capacity = initialSize;
		m_UsedElements = 0;
	}

	// DynamicArray's destructor
	~DynamicArray()
	{
		delete[] m_Data;
		m_Data = nullptr;
	}

	// Adds another element to the begining of the array
	void Add(T value)
	{
		CheckForResize();
		
		// Always puts the new data at the first free element of the array
		m_Data[m_UsedElements] = value;
		m_UsedElements++;
	}
	
	// Adds another element at a specified point in the array
	void InsertAt(int index, T value)
	{
		CheckForResize();

		// Shifts all the data in the array allowing for the new data to be inserted
		for (int i = m_UsedElements - 1; i >= index; i--)
		{
			m_Data[i + 1] = m_Data[i];
		}

		// Inserts the data into the element
		m_Data[index] = value;
		m_UsedElements++;
	}

	// Removes the elemet specified by its value
	void Remove(T value)
	{
		int index = Find(value);

		// Shifts the data after the specified element down one to occypy the element
		for (int i = index; i < m_UsedElements; i++)
		{
			m_Data[i] = m_Data[i + 1];
		}

		m_UsedElements--;
	}

	// Removes the element specified from its index
	void RemoveAt(int index)
	{
		// The selected index doesnt exist
		if (index > m_UsedElements || index < (m_UsedElements - m_UsedElements))
		{
			std::cout << "The index specified is not within the range of the current array" << std::endl;
		}

		else
		{
			// Shifts the data to occupy the data over the selected element
			for (int i = index; i < m_UsedElements; i++)
			{
				m_Data[i] = m_Data[i + 1];
			}
			m_UsedElements--;
		}
	}

	// Finds the index of a selected value
	int Find(T value)
	{
		int index = 0;
	
		// Cycles through all elements untill it reaches the correct one
		for (int i = 0; i < m_UsedElements; ++i)
		{
			if (m_Data[i] == value)
			{
				index = i;
			}
		}

		return index;
	}

	// Allows [] operators to act as an array index 
	T& operator[] (int index)
	{
		return m_Data[index];
	}

	// Returns the size of the current array
	int GetSize()
	{
		return m_UsedElements;
	}

	// Returns the capacity of the current array
	int GetCapacity()
	{
		return m_Capacity;
	}

	// Clears the array
	void Clear()
	{
		m_UsedElements = 0;
	}

	// Allowws to remove cells
	void RemoveSize(int size)
	{
		m_UsedElements -= size;
	}

	// Allows to remove cells
	void Addsize(int size)
	{
		m_UsedElements += size;
	}

private:

	// Checks for and resizes array if needed
	void CheckForResize()
	{
		// Creates a larger array and occupies it with current data
		if (m_UsedElements >= m_Capacity)
		{
			m_Capacity *= 2;
			T* newData = new T[m_Capacity];

			// Transfers data from one array tothe other
			std::memcpy(newData, m_Data, sizeof(T) * m_UsedElements);

			delete m_Data;
			m_Data = newData;
		}
	}

	// Contains any data type
	T* m_Data;

	// Stats on the array
	int m_Capacity;
	int m_UsedElements;
};