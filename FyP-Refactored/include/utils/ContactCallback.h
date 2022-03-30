#ifndef CONTACT_CALLBACK_H
#define CONTACT_CALLBACK_H

#include <functional>
#include <iostream>

class IShape;

using FunctionPtr = std::function<void(IShape*)>;

class ContactCallback
{
public:
	ContactCallback() = default;
	~ContactCallback() = default;

	/// <summary>
	/// function to set the callback function
	/// </summary>
	/// <param name="t_func"> function to call </param>
	virtual void operator()(FunctionPtr t_func)
	{
		m_callback = t_func;
	}

	/// <summary>
	/// operator to invoke the callback function
	/// </summary>
	/// <param name="t_collider"> object it collided with </param>
	virtual void operator()(IShape* t_collider)
	{
		if (m_callback)
			m_callback(t_collider);
	}

private:
	FunctionPtr m_callback;
};
#endif