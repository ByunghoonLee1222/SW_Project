library ieee;
use ieee.std_logic_1164.all;

entity RSF_2 is
	port ( gamestart : in std_logic ;
			 play1, play2 : in std_logic_vector ( 2 downto 0 );
			winflag : in std_logic; 
			button1 : in std_logic;
			rsf2_start : in std_logic; -- check1
			clk : in std_logic;
			rsf_check1, rsf_check2 : out std_logic;
			rsf_led1, rsf_led2 : out std_logic;
			winner : out std_logic
			
			 );
end RSF_2;

architecture sample of RSF_2 is



begin

p3 : process ( play1, play2)  -- rsf_check2 
			variable led1,led2: std_logic;
begin
if gamestart ='1' then
			if ( button1'event and button1='0') then--and rsf2_start = '1' then
		 --if rsf_check2 = '0'  then
			
		--3COUNTDOWN
	--------------------------------------------------------------	
			 if winflag = '1' then  --1P WIN
					if play1 = play2 then
							winner <= '1'; -- p1 win
							rsf_check2 <= '1'; -- rsf2 on end
							rsf_check1 <= '0';
							led1 := '0';
							led2 := '1';
							
					else
					-- restart push0
							rsf_check2 <= '0'; -- reset check
							rsf_check1 <= '0'; -- reset check
							led1 := '0';
							led2 := '0';
							
					end if;
			else --winflag = '0' then -- 2PWIN
					if play1 = play2 then
							winner <= '0'; -- p2 win
							rsf_check2 <= '1'; -- rsf2 on end
							rsf_check1 <= '0';
							led1 := '0';
							led2 := '1';
					else 
					 -- restart push0
							rsf_check2 <= '0'; -- reset check
							rsf_check1 <= '0'; -- reset check
							led1 := '0';
							led2 := '0';
							
					
					end if;
			end if;
	---------------------------------------------------------------	

		end if;
	end if;
		rsf_led1 <= led1;
		rsf_led2 <= led2;
end process;	



end sample;