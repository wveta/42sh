/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_par_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/09 17:55:13 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_parm_ll(char *tmp)
{
	char	*val;

	ft_strcpy(tmp, tmp + 1);
	if (ft_test_parname(tmp))
		return (tmp = ft_print_badsub(tmp, 0, NULL));
	if ((val = ft_get_env(tmp)))
	{
		tmp[0] = '\0';
		tmp = ft_putfnbr(ft_strlen(val), tmp);
	}
	else
	{
		tmp = ft_print_badsub(tmp, 0, NULL);
		tmp[0] = 0;
//		tmp[0] = '0';
//		tmp[1] = '\0';
	}
	return (tmp);
}

char	*ft_get_parm_qq(char *s)
{
	char	*val;
	int		j;
	char	*tmp;
	char	*tmp2;
	int 	jj;
	int		k = 0;

	if (((j = ft_strchr(s, ':') - s)) > -1)
	{
		tmp = ft_strnew(j + 1);
		tmp = ft_strncpy(tmp, s, j);
		if (ft_test_parname(tmp))
		{
			free(tmp);
			return (s = ft_print_badsub(s, 0, NULL));
		}
		if (!(val = ft_get_env(tmp)))
		{
			if (s[j + 1] == '-' || s[j + 1] == '=' || s[j + 1] == '?')
			{
				val = ft_strnew(ft_strlen(s) - (j + 1) + 1);
				val = ft_strcpy(val, s + j + 2);
				jj = 0;
				while (jj < (int)ft_strlen(val))
				{
					if (val[jj] == '$' && (ft_check_ekran(val, jj)) == 0 &&
						val[jj + 1] && val[jj + 1] == '{')
					{
						tmp2 = ft_strdup(val + jj);
						k = 0;
						tmp2 = ft_repl_subs(tmp2, &k, ft_strlen(tmp2));
						val[jj] = '\0';
						val = ft_strfjoin(val, tmp2);
						free(tmp2);
						if (g_subs_rc == 1)
						{
							free(tmp);
							free(val);
							ft_set_shell("?", "1");
							if (g_subshell == 0)
								return (s);
							else
								exit_shell(1);
						}
					}
					jj++;
				}
				if (s[j + 1] == '=' && tmp && ft_strlen(tmp) > 0)
					ft_set_shell(tmp, val);
				else if  (s[j + 1] == '=' && (!tmp || ft_strlen(tmp) == 0))
				{
					free(tmp);
					free(val);
					return (s = ft_print_badsub(s, 0, NULL));
				}
				else if (s[j + 1] == '?' && val[0] == '\0')
				{
					free(val);
					return (s = ft_print_badsub(s, 1, tmp));
				}
			}
		}
		if (s[j + 1] == '+' && val)
		{
			if (tmp && ft_strlen(tmp) > 0)
			{
				free(tmp);
				free(val);
				val = ft_strnew(ft_strlen(s) - (j + 1) + 1);
				val = ft_strcpy(val, s + j + 2);
				jj = 0;
				while (jj < (int)ft_strlen(val))
				{
					if (val[jj] == '$' && (ft_check_ekran(val, jj)) == 0 &&
						val[jj + 1] && val[jj + 1] == '{')
					{
						tmp2 = ft_strdup(val + jj);
						k = 0;
						tmp2 = ft_repl_subs(tmp2, &k, ft_strlen(tmp2));
						val[jj] = '\0';
						val = ft_strfjoin(val, tmp2);
						free(tmp2);
						if (g_subs_rc == 1)
						{
//							free(tmp);
							free(val);
							ft_set_shell("?", "1");
							if (g_subshell == 0)
								return (s);
							else
								exit_shell(1);
						}
					}
					jj++;
				}
			}
			else
			{
				g_subs_rc = 1;
				ft_print_msg(": parameter not exist: ", s);
				ft_set_shell("?", "1");
				free(tmp);
				free(val);
				return (s);
			}
		}
		else
			free(tmp);
		free(s);
		if (!(val))
			val = ft_strdup("");
		return (val);
	}
	return (s);
}

char	*ft_get_parm_rr(char *s)
{
	char	*val;
	int		j;
	char	*tmp;
	char	*flag;

	int		jj;
	int		k;

				jj = 0;
				while (jj < (int)ft_strlen(s))
				{
					if (s[jj] == '$' && (ft_check_ekran(s, jj)) == 0 &&
						s[jj + 1] && s[jj + 1] == '{')
					{
						tmp = ft_strdup(s + jj);
						k = 0;
						tmp = ft_repl_subs(tmp, &k, ft_strlen(tmp));
						s[jj] = '\0';
						s = ft_strfjoin(s, tmp);
						free(tmp);
						if (g_subs_rc == 1)
						{
							ft_set_shell("?", "1");
							if (g_subshell == 0)
								return (s);
							else
								exit_shell(1);
						}
					}
					jj++;
				}



	if (((j = ft_strchr(s, '#') - s)) > 1)
	{
		tmp = ft_strnew(j + 1);
		tmp = ft_strncpy(tmp, s, j);
		if (ft_test_parname(tmp))
		{
			free(tmp);
			return (s = ft_print_badsub(s, 0, NULL));
		}
		if (s[j + 1] == '#')
		{
			flag = ft_strdup("##");
			j++;
		}
		else
			flag = ft_strdup("#");
		if ((val = ft_get_env(tmp)))
		{
			free(tmp);
			tmp = ft_strnew(ft_strlen(s) - j + 1);
			tmp = ft_strcat(tmp, s + j + 1);
			val = param_rem(val, flag, tmp);
		}
		else
			val = ft_strdup("");
		free(tmp);
		free(s);
		free(flag);
		return (val);
	}
	return (s);
}

char	*ft_get_parm_prc(char *s)
{
	char	*val;
	int		j;
	char	*tmp;
	char	*flag;

	int		jj;
	int		k;

				jj = 0;
				while (jj < (int)ft_strlen(s))
				{
					if (s[jj] == '$' && (ft_check_ekran(s, jj)) == 0 &&
						s[jj + 1] && s[jj + 1] == '{')
					{
						tmp = ft_strdup(s + jj);
						k = 0;
						tmp = ft_repl_subs(tmp, &k, ft_strlen(tmp));
						s[jj] = '\0';
						s = ft_strfjoin(s, tmp);
						free(tmp);
						if (g_subs_rc == 1)
						{
							ft_set_shell("?", "1");
							if (g_subshell == 0)
								return (s);
							else
								exit_shell(1);
						}
					}
					jj++;
				}






	if (((j = ft_strchr(s, '%') - s)) > 1)
	{
		tmp = ft_strnew(j + 1);
		tmp = ft_strncpy(tmp, s, j);
		if (ft_test_parname(tmp))
		{
			free(tmp);
			return (s = ft_print_badsub(s, 0, NULL));
		}
		if (s[j + 1] == '%')
		{
			flag = ft_strdup("%%");
			j++;
		}
		else
			flag = ft_strdup("%");
		if ((val = ft_get_env(tmp)))
		{
			free(tmp);
			tmp = ft_strnew(ft_strlen(s) - j + 1);
			tmp = ft_strcat(tmp, s + j + 1);
/*			if (ft_strncmp(val, tmp, ft_strlen(tmp)) == 0)
				val = ft_strcpy(val, val + ft_strlen(tmp));*/
			val = param_rem(val, flag, tmp);
		}
		else
			val = ft_strdup("");
		free(tmp);
		free(s);
		free(flag);
		return (val);
	}
	return (s);
}

char	*ft_repl_subs(char *s, int *k, int i)
{
	char	*tmp;
	char	*ret;
	int		j;
	int		n;

	if (ft_test_parname(s + 2))
		return (s = ft_print_badsub(s, 0, NULL));
	if ((j = ft_subst_lbr(s + *k + 2)) == -1)
		j = ft_strlen(s + *k + 2);
	tmp = ft_alloc_char(j + 1);
	tmp[j] = '\0';
	tmp = ft_strncpy(tmp, s + *k + 2, j);
	n = -1;
	while (tmp[++n] && ft_check_ekran(tmp, n) == 0)
	{
		if (tmp[n] == '#' && n == 0 && (n = -7))
		{
			tmp = ft_get_parm_ll(tmp);
			break;
		}
		else if (tmp[n] == ':' && (n = -7))
		{
			tmp = ft_get_parm_qq(tmp);
			break;
		}
		else if (tmp[n] == '#' && (n = -7))
		{
			tmp = ft_get_parm_rr(tmp);
			break;
		}
		else if (tmp[n] == '%' && (n = -7))
		{
			tmp = ft_get_parm_prc(tmp);
			break;
		}
	}
	if (n != -7)
	{
		if (ft_test_sub(s + *k + 2, i - 2) == 1)
			return (s);
		tmp = ft_get_parm_simple(tmp);
	}
	ret = ft_alloc_char(*(k) + ft_strlen(tmp) + ft_strlen(s) + 1);
	ret[0] = '\0';
	ret = ft_strncat(ret, s, *(k));
	ret = ft_strcat(ret, tmp);
	if ((int)ft_strlen(s) > *k + 2 + j + 1)
		ret = ft_strcat(ret, s + *k + 2 + j + 1);
	free(tmp);
	free(s);
	return (ret);
}
