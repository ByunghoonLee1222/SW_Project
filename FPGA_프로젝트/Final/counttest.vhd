library ieee;
use ieee.std_logic_1164.all;

entity counttest is

	port ( clk_count,reset : in std_logic;
		   counta_dec : out std_logic_vector(6 downto 0) );

end counttest;

architecture sample of counttest is

	function dis_seg( cnt : integer range 0 to 15 ) return std_logic_vector is
	variable seg_decode : std_logic_vector(6 downto 0);
	
	begin
		case cnt is
		when 0 => seg_decode := "1000000";
		when 1 => seg_decode := "1111001";
		when 2 => seg_decode := "0100100";
		when 3 => seg_decode := "0110000";
		when 4 => seg_decode := "0011001";
		when 5 => seg_decode := "0010010";
		when 6 => seg_decode := "0000010";
		when 7 => seg_decode := "1011000";
		when 8 => seg_decode := "0000000";
		when 9 => seg_decode := "0011000";
		when others => seg_decode := "1111111";

		end case;
	return (seg_decode);
	end dis_seg;

	signal counta : integer range 0 to 9;

	begin
		a_counter : process(clk_count,reset)

	begin
		if reset = '1' then
			counta <= 9;
		elsif (clk_count'event and clk_count='1') then
			if counta = 0 then
				counta <= 9;
			else
				counta <= counta - 1;
			end if;
		end if;
end process;

counta_dec <= dis_seg( counta );
end sample;