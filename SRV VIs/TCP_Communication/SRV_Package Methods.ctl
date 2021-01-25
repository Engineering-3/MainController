RSRC
 LVCCLBVW  "4  `      "   � �  0           < � @�      ����            �=�*YL��3�!K          ���Li�G��p�ж����ُ ��	���B~                                                        LVCC              "   x�c`c`j`�� Č@������ �3  h6     H  x�c`��� H1200��,h�`Ʀ&�e..����P7�BD�bL{�&�T���) >�n�{j(    VIDS       Y  4x�3`d`�4�0[ ���X���!9?%���g� &8p�҆��`F��O���@s���P��GE��G���E�X����9�m@�n��qH����� U��� �i��-,`�o0�Z32�0�b�{��yҺA�
�Y3�O9�����r~׃ �2���Rs�!KwcP�w"�
�t�pHw���b<�	tR'�������@��t��\���f;�q��`*���� S@�;@д��M��3��_� g-� �mvi= ��� i r ;$�8�001�2�0F3&1f2�1�0�(����̇� �!^y         	x�c```dd         �6  14.0     �   14.0     �6  14.0     �   14.0     �6  14.0                      Y  UEnumerates the methods for reading from a TCP connection:

<B>General</B> (Immediate) - Waits until the function receives any bytes from those you specify in bytes to read. Waits the full timeout only if the function receives no bytes. Returns the number of bytes so far. Reports a timeout error if the function receives no bytes.

<B>Standard</B> - Waits until all bytes you specify in bytes to read arrive or until timeout ms runs out. Returns the number of bytes read so far. If fewer bytes than the number of bytes you requested arrive, returns the partial number of bytes and reports a timeout error.

<B>CRLF</B> - Waits until all bytes you specify in bytes to read arrive or until the function receives a CR (carriage return) followed by a LF (linefeed) within the number of bytes you specify in bytes to read or until timeout ms runs out. Returns the bytes up to and including the CR and LF. When the function does not find a CR and LF, but there are at least bytes to read bytes available, the function returns those bytes. When the function does not find a CR and LF and there are less bytes available than the number of bytes you specify in bytes to read, the function returns no bytes and reports a timeout error.

<B>Image</B> - Calls "SRV_Read JPG.vi".

<B>HTML</B> - Does a Standard TCP read of HTTP/1.1 200 OK...


Modified: Mike Schultz - Logic PD
      ����0  @  @  �  �  �����*3��:������  �  �  �  ��I���US�	�K��I��  �  �  �  �  �  �  �  �  �  @  @  ?������      +������������������������+     ��++++++++++++++++++++++++��   �++%%%%%%%%%%%%%%%%%%%%%%%%++� +�+%%%%%%%%%%%%%%%%%%%%%%%%%%+�+�+%%%%%%%%%%%%%%%%%%%%%%%%%%%%���+%%%%%%%%%%%%%%%%%%%%%%%%%%%%���+��%%%�%%%��%�%�%%�%%%��%���%���+�%�%�%�%�%%%��%%�%�%�%%%��%%���+��%%���%�%%%��%%���%�%�%�%%%���+�%%%�%�%%��%�%�%�%�%%��%���%���+%%%%%%%%%%%%%%%%%%%%%%%%%%%%���+%%%%%%%%%%%%%%%%%%%%%%%%%%%%���+%%%%%%%%%%%%%%%%%%%%%%%%%%%%���+%%%%%%%%%%%%%%%%%%%%%%%%%%%%���+�%%�%���%���%�%�%%�%%��%%��%���+����%��%%%�%%�%�%�%�%�%�%�%%���+�%%�%�%%%%�%%���%�%�%�%�%%�%���+�%%�%���%%�%%�%�%%�%%��%%��%���+%%%%%%%%%%%%%%%%%%%%%%%%%%%%���+%%%%%%%%%%%%%%%%%%%%%%%%%%%%���+%%%%%%%%%%%%%%%%%%%%%%%%%%%%���+%%%%%%%%%%%%%%%%%%%%%%%%%%%%���+%%%%%%%%%%%%%%%%%%%%%%%%%%%%���+%%%%%%%%%%%%%%%%%%%%%%%%%%%%���+%%%%%%%%%%%%%%%%%%%%%%%%%%%%���+%%%%%%%%%%%%%%%%%%%%%%%%%%%%���+%%%%%%%%%%%%%%%%%%%%%%%%%%%%���+%%%%%%%%%%%%%%%%%%%%%%%%%%%%��+�+%%%%%%%%%%%%%%%%%%%%%%%%%%��+ �++%%%%%%%%%%%%%%%%%%%%%%%%���   ����������������������������     +������������������������+             FPHP       �  
:x��VML�VNC�d0�V�v�#rR�H�VUU(m�2��&UN��Xrlf;P.�Q%=!q����;p��qئ��\&;����^z�619��=�I�|tӂb,�������P��0j�/]�	/�&R��ex���p��q�q�E񷅧�&w�E�J=���Fg�&�o�gzZ�Y�E�J�l����΋]k�/<⚡O�ğ���	��:D���D�4W��A�"}��qFq� �{,�qA�F�m"�}J�Ch{{��y�4�q�b\@��m���-6F&�0�&`|)�ܤ�)� ��H�=2v))�~|(��~�1���g��]=�T�G�j��V����n�&��>�Cj�����>T�a�e��,z��p&h�4��aM�H��۷��O��%O� N�T4�e@5���Bۏ>G)���b,���]Huoo����á�H�D2U'�ͩ>m���R=rQlt3Vo��Q/��9�U�!Ę�s-;xf�Ēu~ёE����B~�k�,�'�K7�n��FA���1�˦2>��Akgg��K@eCB�k�µ���n�,d�^��?E>I�_��ڂP���$:nr^N17��n���wSxs7�}n`����Y��n� �3���A�4�NIg�!���g(������ma����:εx�klڨ��K��S"���ƪia�Ȋf�Ǫe������q�4Rt4��F'&��-�������e�h@5�3���96���3b�b0���
r����T�	��M�Y��
)j�:���c2/Y�ԣӁW+��`��!Z=B�0=�,^ N�2<H�@,l���mbU�h̊i���f'��8��$�uV��U����u\�X�,�� �ϷQ��U�p|&�%HgN�*Y�׾HI6QK��Bl�F�IGfE�M�_CB�whѼ��U�?���Y�Sx�H�aw�}�뺹	�!$?��t� *!�0^Ӝ�vt1�4���p�
�UҌ�^a+����a~ƺD���)&�,��ȝ�\ I����։l;L��Y�5].���eL�%�/�a���xЉmT<~Ҏ*�>�%v�ئ`�l�\\�so�����lvUKz���Ǐ�L6@��e���i_]Z�ˎዹ�u=��F#�rj<�~Jc�l��(��Sy�/�Rv�l��O*��0�W.zW���I���0?�O��P�������o��\-�FV�я�7	~�vG:                 BDHP        b   rx�c``��`��P���I�+�!���YЏ�7���a �( 	����.��>��� �l���9�2-�����z�\�8Se�<� b           n      NI_IconEditor �     @0����Data      709008022    Load & Unload.lvclass       	  ddPTH0     SRV_TCP.png  � (  �                 ���  ������������wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww������������������wwwwww������������������������������������������������������������������������wwwwww���������www������������������������������������������������������������������������������������   ������www������������������������������������������������������������������������������������   ���www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   www���������������������������������������������������������������������������������������www   ���www���������������������������������������������������������������������������������www   ������www������������������������������������������������������������������������������wwwwww   ���������      wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww      ������������������                                                                        ���������������?�����������������������������������������������������������������������������������������������������������������?������       Package   Methods          A�  A�           Small Fonts                  K   (                                        �                    $     LUUA N 	                                                   ��*>��*>��*>��*>     L   ?           �  dx����JA����_�?QA^����!*$�lԫ���Y�#x���8>���e6���4�U��5�.W|��� f�_�dnz�f�`\���x<����t�0>+�����Ļy�Ep����Ń^��D��k�3v5r����ت���/��}K�ME?ͤ�D����$DX�\h9�CB���g鰴T1��V1�r�Ά�ol���
�_ek��S��Q:t,�c����]4?   e       H      � �   Q      � �   Z      � �   c� � �   � �Segoe UISegoe UISegoe UI0   RSRC
 LVCCLBVW  "4  `      "               4  H   LVSR      lRTSG      �CCST      �LIvi      �CONP      �TM80      �DFDS      �LIds      �VICD      GCDI       vers     4GCPR      �STRG      �ICON      �icl8      �CPC2      �LIfp      �FPHb      FPSE      $VPDP      8LIbd      LBDHb      `BDSE      tVITS      �DTHP      �MUID      �HIST      �PRT       �VCTP      �FTAB                               ����       �        ����       �        ����       �        ����       �        ����       �        ����       �        ����      8        ����      H        ����      �       ����      �       ����      �       ����      �       	����      �       
����               ����              ����      $        ����      �        ����      	        ����              ����              ����      $        ����      �        ����               ����              ����              ����      �        ����      �        ����      �        ����               ����               ����       8        ����       �       �����      !�    SRV_Package Methods.ctl