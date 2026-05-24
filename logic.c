#include "rush02.h"

void	run_standard_input_mode(char *dict_file)
{
	char	buf;
	int		i;

	char input_buffer[4096]; // กล่องสะสมตัวอักษรที่ผู้ใช้พิมพ์สด
	i = 0;
	// วนลูปอ่านค่าจากคีย์บอร์ดทีละ 1 ตัวอักษร (fd = 0)
	// ลูปนี้จะรันค้างไว้เรื่อย ๆ จนกว่าผู้ใช้จะกด Ctrl+D (read จะคืนค่าเป็น 0)
	while (read(0, &buf, 1) > 0)
	{
		if (buf == '\n') // ถ้าผู้ใช้กดปุ่ม Enter (ขึ้นบรรทัดใหม่)
		{
			input_buffer[i] = '\0'; // ปิดท้ายสตริงข้อความที่เขาพิมพ์มา
			// 1. หยิบฟังก์ชันตรวจตัวเลขตัวเดิมมาสแกนตรวจสายอักษรที่พิมพ์สดมา
			if (check_invalid_input(input_buffer) == 0)
			{
				// (ฟังก์ชัน check_invalid_input มันจะพ่น Error\n ให้เราอยู่แล้ว)
			}
			else
			{
				// 2. ถ้าผ่าน! ส่งกล่องข้อความนี้ไปให้ระบบแปลงเลขเป็นตัวหนังสือ (Logic)
				// write(1, "Valid! Send to logic\n", 21);
			}
			i = 0; // รีเซ็ตตัวนับ เพื่อเตรียมสะสมตัวเลขในบรรทัดถัดไป
		}
		else
		{
			input_buffer[i] = buf; // สะสมตัวอักษรที่พิมพ์เข้ามาเข้ากล่อง
			i++;
		}
	}
}

#include "rush02.h"

// ฟังก์ชันค้นหาคำอ่านจากคีย์ในพจนานุกรม
char	*find_in_dict(t_dict *dict, int size, char *key)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (dict[i].key[j] && key[j] && dict[i].key[j] == key[j])
			j++;
		if (dict[i].key[j] == '\0' && key[j] == '\0')
			return (dict[i].value);
		i++;
	}
	return (NULL);
}

// แปลงกลุ่มตัวเลข 3 หลัก (เช่น "123" -> one hundred twenty three)
int	print_three_digits(t_dict *dict, int size, char *str)
{
	char	tmp[4];
	char	*res;

	// จัดการหลักร้อย (ถ้าอักขระตัวแรกไม่ใช่ '0')
	if (str[0] != '0')
	{
		tmp[0] = str[0];
		tmp[1] = '\0';
		res = find_in_dict(dict, size, tmp);
		if (!res)
			return (0);
		write(1, res, ft_strlen(res));
		write(1, " ", 1);
		res = find_in_dict(dict, size, "100");
		if (!res)
			return (0);
		write(1, res, ft_strlen(res));
		if (str[1] != '0' || str[2] != '0')
			write(1, " ", 1);
	}
	// จัดการหลักสิบและหลักหน่วย (เคสเลข 10-19)
	if (str[1] == '1')
	{
		tmp[0] = str[1];
		tmp[1] = str[2];
		tmp[2] = '\0';
		res = find_in_dict(dict, size, tmp);
		if (!res)
			return (0);
		write(1, res, ft_strlen(res));
	}
	else
	{
		// หลักสิบปกติ (20, 30, ...)
		if (str[1] != '0')
		{
			tmp[0] = str[1];
			tmp[1] = '0';
			tmp[2] = '\0';
			res = find_in_dict(dict, size, tmp);
			if (!res)
				return (0);
			write(1, res, ft_strlen(res));
			if (str[2] != '0')
				write(1, " ", 1);
		}
		// หลักหน่วย
		if (str[2] != '0')
		{
			tmp[0] = str[2];
			tmp[1] = '\0';
			res = find_in_dict(dict, size, tmp);
			if (!res)
				return (0);
			write(1, res, ft_strlen(res));
		}
	}
	return (1);
}

// สร้างคีย์มาตราวัดความใหญ่ของเลข เช่น 1 แล้วตามด้วยศูนย์ 3 ตัว (Thousand) หรือ 6 ตัว (Million)
static char	*make_suffix_key(int zero_count)
{
	char	*key;
	int		i;

	key = malloc(sizeof(char) * (zero_count + 2));
	if (!key)
		return (NULL);
	key[0] = '1';
	i = 1;
	while (i <= zero_count)
		key[i++] = '0';
	key[i] = '\0';
	return (key);
}

// ฟังก์ชันหลักในการรันโหมดปกติ (รับ dict และเลขสตริงมาประมวลผล)
void	run_normal_mode(char *dict_file, char *num_str)
{
	t_dict	*dict;
	int		dict_size;
	int		len;
	int		groups;
	int		i;
	char	chunk[4];
	char	*suffix;
	int		start;
	int		c;
	char	*suffix_key;

	dict = parse_dict(dict_file, &dict_size);
	if (!dict)
	{
		write(1, "Dict Error\n", 11);
		return ;
	}
	// เคสพิเศษ: ถ้าเป็นเลข 0 ตัวเดียวโดด ๆ
	if (num_str[0] == '0' && num_str[1] == '\0')
	{
		suffix = find_in_dict(dict, dict_size, "0");
		if (suffix)
			write(1, suffix, ft_strlen(suffix));
		write(1, "\n", 1);
		return ;
	}
	len = ft_strlen(num_str);
	groups = (len + 2) / 3; // คำนวณว่ามีเลขทั้งหมดกี่ชุด ชุดละ 3 หลัก
	i = 0;
	while (groups > 0)
	{
		// ดึงตัวเลขทีละ 3 ตัวจากสตริงใหญ่มาใส่กล่อง chunk
		start = len - (groups * 3);
		c = 0;
		while (c < 3)
		{
			if (start < 0)
				chunk[c] = '0';
			else
				chunk[c] = num_str[start];
			start++;
			c++;
		}
		chunk[3] = '\0';
		// ถ้ากลุ่ม 3 หลักนี้ไม่ใช่ "000" ให้สั่งปริ้นคำอ่านของมันออกจอ
		if (!(chunk[0] == '0' && chunk[1] == '0' && chunk[2] == '0'))
		{
			if (!print_three_digits(dict, dict_size, chunk))
			{
				write(1, "Dict Error\n", 11);
				return ;
			}
			// ใส่คำสร้อยมาตราวัดตามท้ายกลุ่ม (เช่น thousand, million)
			if (groups > 1)
			{
				suffix_key = make_suffix_key((groups - 1) * 3);
				suffix = find_in_dict(dict, dict_size, suffix_key);
				free(suffix_key);
				if (!suffix)
				{
					write(1, "Dict Error\n", 11);
					return ;
				}
				write(1, " ", 1);
				write(1, suffix, ft_strlen(suffix));
				write(1, " ", 1);
			}
		}
		groups--;
	}
	write(1, "\n", 1);
}
