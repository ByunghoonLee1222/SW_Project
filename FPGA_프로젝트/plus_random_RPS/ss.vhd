library ieee;
use ieee.std_logic_1164.all;

entity ss is
		port ( 
				clk : in std_logic;  -- clk : play2 random
				clk1hz : buffer std_logic;
				
				play2_output : out std_logic_vector(2 downto 0));
end ss;

architecture sample of ss is
	
	signal cnt1: integer range 0 to 50000000;
				
	signal counta : integer range 0 to 9;
	signal random : std_logic_vector (3 downto 0);
	signal play2 : std_logic_vector (2 downto 0);
	
	
begin

	play2_output <= play2;
	
	
		p2 : process(clk) begin
if clk'event and clk='1' then
if cnt1 = 50000000 then
cnt1 <= 0; clk1hz <= '1'; else
cnt1 <= cnt1 + 1; clk1hz <= '0';
 end if; 
 end if; 
 end process;
	
		
	s1 : process(clk,random)
			
			
			begin
			
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
			
			if clk'event and clk='1' then  -- clk rising edge
						
					random(0) <= random(1); -- (1)value -> shift -> (0)
					random(1) <= random(2); -- (2)value -> shift -> (1)
					random(2) <= random(3); -- (3)value -> shift -> (2)
					random(3) <= random(0) xor random(1); -- (0) xor (1) -> (3) : value change
				
				
			end if;

			
	end process;

	
end sample;