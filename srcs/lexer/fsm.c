#include "lexer_internal.h"

/**
 * fsm_update
 * @brief Updates the current state based on the input character.
 * * [Transition Table]
 * - Q_NONE   + ' -> Q_SINGLE
 * - Q_NONE   + " -> Q_DOUBLE
 * - Q_SINGLE + ' -> Q_NONE
 * - Q_DOUBLE + " -> Q_NONE
 * - Default       -> Keep current state
 *
 * @param state Pointer to the current quote state.
 * @param c     The character to process.
 */
void	fsm(t_qstate *state, char c)
{
	if (*state == QUOTE_NONE)
	{
		if (c == '\'')
			*state = QUOTE_SINGLE;
		else if (c == '\"')
			*state = QUOTE_DOUBLE;
	}
	else if (*state == QUOTE_SINGLE && c == '\'')
		*state = QUOTE_NONE;
	else if (*state == QUOTE_DOUBLE && c == '\"')
		*state = QUOTE_NONE;
}
