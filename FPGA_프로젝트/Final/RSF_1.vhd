library ieee;
use ieee.std_logic_1164.all;

entity RSF_1 is
		port (  gamestart : in std_logic ;
				play1, play2 : in std_logic_vector ( 2 downto 0 );
				rsf1_start,rsf2_start : in std_logic;
				button0 : in std_logic ;
				clk : in std_logic;
				RSF2_count : in std_logic;
				smcount : out std_logic;
				rsf_check1: out std_logic;
				rsf_led1 : out std_logic;
				countSeg : out std_logic_vector(6 downto 0);
				winflag : out std_logic
				
				);
end RSF_1;

architecture sample of RSF_1 is
				
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


p1 : process( play1 ,play2,clk,button0)  -- rsf_check1
		variable samecount : std_logic;
		variable winflag1 : std_logic;
		variable led1 : std_logic;
begin
	
if gamestart = '1' then ----------------1

if RSF2_count = '0' then  -- one RSF2 ----------------------2

	if rsf1_start = '0' and rsf2_start = '0' then -- RSF1 Check

---------------------------------counnt start -----------
	
		if (clk'event and clk='1') then -- clk count
			if counta = 0 then------------------count end
				counta <= 5;
		
		
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
		else  ----- count 3
			counta <= counta - 1;
			end if;  -- count if
			
countSeg <= dis_seg( counta );
			
		end if; -- clk if
	end if; -- RSF1 Check
	--end if;
	
else -- RSF2_count = '1';
	
	
	if rsf1_start = '0' and rsf2_start = '0' then -- RSF1 Check

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
		end if; -----------RSF1 Check

end if;----------RSF2 one
	
end if;-------------------check1


	rsf_led1 <= led1;
	
	winflag <= winflag1;
	
end process;	
	
end sample;


