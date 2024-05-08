/*
 ============================================================================
 Name        : Errors.h
 Author      : Farah Mohey
 Description : Header file for Errors
 Created	 : 15-Feb-24
 ============================================================================
 */

#ifndef ERRORS_ENUM_H_
#define ERRORS_ENUM_H_


typedef enum
{
	Ok,		/*Everything Ok */
	Nok,	/*Everything NOk */

	ONFailed,		/*Failed to Make this process ON*/
	OFFFailed,		/*Failed to Make this process OFF*/

	WrongInput, 	/*User enter wrong input*/

	NullPointer,

	RCC_ClkReady,		/* RCC Clock is Ready */
	RCC_ClkNotReady,	/* RCC Clock is Not Ready */

}enumError_t;


#endif /* ERRORS_ENUM_H_ */
