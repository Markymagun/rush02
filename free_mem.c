#include "rush02.h"

void	free_dict(t_dict *dict)
{
	int	i;

	if (!dict)
		return ;
	i = 0;
	while (dict[i].key != NULL)
	{
		free(dict[i].key);
		if (dict[i].value)
			free(dict[i].value);
		i++;
	}
	free(dict);
}
