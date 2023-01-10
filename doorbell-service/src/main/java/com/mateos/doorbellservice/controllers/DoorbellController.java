package com.mateos.doorbellservice.controllers;

import com.mateos.doorbellservice.request.RingRequest;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class DoorbellController {

    Logger logger = LoggerFactory.getLogger(DoorbellController.class);

    @PostMapping(value = "/ring")
    public void ring(@RequestParam(name="value", required=true) String value) {
        logger.info("Sound level = " + value);
    }

    @PostMapping(value = "/alive")
    public void alive(@RequestParam(name="uuid", required=true) String uuid) {
        logger.info("ALIVE = " + uuid);
    }
}
