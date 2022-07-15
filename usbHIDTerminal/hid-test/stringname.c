 uint8_t btid[5];
    btid[0] = ' ';
    btid[1] = '#';
    btid[2] = '0';
    btid[3] = '1';
    
    uint8_t id_len = strlen(btid);
    uint8_t btid_size = sizeof(btid)/sizeof(btid[0]);
    
    printf("string : %s \n", btid);
    printf("size : %u \n", btid_size);  // include null char terminate
    printf("len : %u \n", id_len);    // only chars 
    
    // uint8_t new_name[20] = "Cloud BT-2";
    uint8_t new_name[20] = "StarsElectronics";
    
    
    uint8_t new_name_size = sizeof(new_name)/sizeof(new_name[0]);
    uint8_t new_name_len = (unsigned)strlen(new_name);
    printf("string : %s \n", new_name);
    printf("size : %u \n", new_name_size);  // include null char terminate
    printf("len : %u \n", new_name_len);    // only chars 
    
    printf("**********************************************\n");
    
    uint8_t new_name2[new_name_len+1];
    strcpy(new_name2,new_name);
    uint8_t new_name2_size = sizeof(new_name2)/sizeof(new_name2[0]);
    uint8_t new_name2_len = (unsigned)strlen(new_name2);
    
    
    printf("string : %s \n", new_name2);
    printf("size : %u \n", new_name2_size);  // include null char terminate
    printf("len : %u \n", new_name2_len);    // only chars 
    
    printf("**********************************************\n");
    
    uint8_t new_name3_size = new_name2_len + btid_size;
    uint8_t new_name3[new_name3_size];
    
    strcpy(new_name3, new_name2);
    // strcat(new_name3, " #01");
    strcat(new_name3, btid);
    
    uint8_t new_name3_len = (unsigned)strlen(new_name3);
    
    printf("string : %s \n", new_name3);
    printf("size : %u \n", new_name3_size);   // include null char terminate
    printf("len : %u \n", new_name3_len);  // only chars 
    