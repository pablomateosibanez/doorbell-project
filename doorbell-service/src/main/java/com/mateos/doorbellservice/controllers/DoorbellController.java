package com.mateos.doorbellservice.controllers;

import com.mateos.doorbellservice.request.RingRequest;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class DoorbellController {

    @PostMapping(value = "/ring",
            consumes = {MediaType.APPLICATION_JSON_VALUE})
    public void ring(RingRequest ringRequest) {
        System.out.println(ringRequest.getValue());
    }
}
