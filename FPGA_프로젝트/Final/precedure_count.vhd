library ieee;
use ieee.std_logic_1164.all;

entity precedure_count is
		port ( play1, play2 : in std_logic_vector ( 2 downto 0 );
			 button0, button1 : in std_logic;
			clk : in std_logic;
			SEGcount : out std_logic_vector(6 downto 0);
			smcount :out std_logic;
			rsf_led1 , rsf_led2 : out std_logic;
			winner : out std_logic
			
			 );
		end  precedure_count ;
		
architecture sample of precedure_count is

function dis_seg( cnt : integer range 0 to 9 ) return std_logic_vector is
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


procedure calc( clk : in std_logic;
					counta : in integer range 0 to 3; 
					endcount : out std_logic) is
		begin
			if (clk'event and clk='1') then
					if counta = 0 then
							counta := 3;
							endcoubt := '1';
					else 
							counta := counta -1 ;
					end if;
			end if;
			end calc;
					


signal count : integer range 0 to 9;
signal count_out : std_logic;



signal rsf_check1, rsf_check2, rsf_check3: std_logic := '0';

signal winflag : std_logic := '0' ;

signal counta : integer range 0 to 3 := 3;


signal srfcount : integer range 0 to 2 := 0;

begin

p1 : process( play1 ,play2,clk,button0)  -- rsf_check1
		variable samecount : std_logic;
		variable winflag1 : std_logic;
		variable led1 : std_logic;
begin
	--if rsf_check1 = '0' then  -- and  push 0 
	
	--if rsf_check1 = '0' then   -- count start
	
	if ( button0'event and button0='1') then
	
	
	--if (clk'event and clk='1') then
	--		if counta = 0 then
		--		counta <= 3;
		
		
	---------------------------------------------
	if play1 = play2 then   -- p1 p2 same??
		samecount :=  '1';
		
		
	else
		samecount :=  '0';
	end if;
	------------------------------------------------
	
	
	smcount <= samecount;
	
		case samecount is
		when '0' =>
	
		
		rsf_check1 <= '1';
		led1 := '1';
			case play1 is
			
			when "010" => --scissors
				case play2 is
					when "100" => winflag1 := '0'; --p2 win
					when others => winflag1 := '1'; --p1 win
				end case;
			when "100" => -- rock
				case play2 is
					when "001" =>  winflag1 := '0'; -- p2 win
					when others => winflag1 := '1'; -- p1 win
				end case;
			
			when "001" =>-- paper
				case play2 is
					when "100" => winflag1 := '1';  --p1 win
					when others => winflag1 := '0'; --p2 win
				end case;
			 --error
			when others => 
			
			rsf_check1 <= '0';
			led1 := '0';
			
			end case;
			
		when others =>
		
		rsf_check1 <= '0';
		led1 := '0';
			
		end case;	
	-----------------------------------------------------------------
	
	 -- else 
	--		counta <= counta - 1;
	--	end if;
	
	--end if;
	end if;
	rsf_led1 <= led1;
	SEGcount <= dis_seg( counta );
	winflag <= winflag1;
	
end process;	
end sample;