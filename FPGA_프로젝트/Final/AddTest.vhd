library ieee;
use ieee.std_logic_1164.all;

entity AddTest is
	port (  play1: in std_logic_vector ( 2 downto 0 );
			
			button0 : in std_logic ;
			button1 : in std_logic;
			rst_random_reset : in std_logic;			
			clk_random : in std_logic;
			smcount : out std_logic;
			winflagrsf2 : out std_logic;
			play2out_RSF1 : out std_logic_vector ( 2 downto 0 );
			play2out_RSF2 : out std_logic_vector ( 2 downto 0 );
			rsf_check1 : out std_logic;
			rsf_check2: out std_logic ; -- 1play not  rsf
			winner : out std_logic -- led
						 );
end AddTest;

architecture sample of AddTest is
		signal rsf_checkbit : std_logic := '0';
		signal random : std_logic_vector (3 downto 0);
		signal play2 : std_logic_vector (2 downto 0);
		signal winflag : std_logic;

begin


s1 : process(clk_random,rst_random_reset,random)
		
			begin
			
			
	if clk_random'event and clk_random='1' then  -- clk rising edge
			if random = "0001" then
				play2 <= "100";               --rock
			elsif random = "0010" then
				play2 <= "100";               --rock
			elsif random = "0011" then
				play2 <= "001";               --scissors
			elsif random = "0100" then
				play2 <= "001";               --scissors
			elsif random = "0101" then
				play2 <= "001";               --scissors
			elsif random = "0110" then
				play2 <= "100";               --rock
			elsif random = "0111" then
				play2 <= "010";               --paper
			elsif random = "1000" then
				play2 <= "010";               --paper
			elsif random = "1001" then
				play2 <= "010";               --paper
			elsif random = "1010" then
				play2 <= "100";               --rock
			elsif random = "1011" then
				play2 <= "010";               --paper
			elsif random = "1100" then
				play2 <= "001";               --scissors
			elsif random = "1101" then
				play2 <= "010";               --paper
			elsif random = "1110" then
				play2 <= "001";               --scissors
			else play2 <= "100";              --rock
			end if;
			
			
				if rst_random_reset = '1' then          -- reset 
					random <= "0001";      -- initialization
					
				else				
					random(0) <= random(1); -- (1)value -> shift -> (0)
					random(1) <= random(2); -- (2)value -> shift -> (1)
					random(2) <= random(3); -- (3)value -> shift -> (2)
					random(3) <= random(0) xor random(1); -- (0) xor (1) -> (3) : value change
					
				end if;
				
			end if;
			
			
	end process;



p3 : process ( play1, play2,winflag)  -- rsf_check2 
		
			variable led: std_logic;
			variable samecount : std_logic;
			variable winflag1 : std_logic := '0';
begin




if (button1'event and button1='1') then
	--------------------------------------------------------------	
			 if winflag = '1' then  --1P WIN
					if play1 = play2 then
							winner <= '1'; -- p1 win
							
							
					else
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
			
									rsf_checkbit <= '0';
								
			
								end case;

						
							
					end if;
			else --winflag = '0' then -- 2PWIN
					if play1 = play2 then
							winner <= '0'; -- p2 win
					else 
					 -- restart push0
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
			
									rsf_checkbit <= '0';
									
			
								end case;
							
					
					end if;
			end if;
	---------------------------------------------------------------	
	winflag <= winflag1;
	play2out_RSF1 <= play2;
	end if;
	
	
	
	if (button0'event and button0='1') then	


			---------------------------------------------
			if play1 = play2 then   -- p1 p2 same??
				samecount :=  '1';
		
		
			else
				samecount :=  '0';
			end if;
			------------------------------------------------
	
	
					smcount <= samecount;
	
		case samecount is --------------------RSF1
		when '0' =>
			rsf_check1 <= '1';
		
		
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
		
			
			end case;
			
		when others =>
		
		rsf_check1 <= '0';
		
			
		end case;	
	-----------------------------------------------------------------
		winflag <= winflag1;
play2out_RSF2 <= play2;
end if;		

	
	
	
	rsf_check2 <= rsf_checkbit;
end process;	
   















end sample;