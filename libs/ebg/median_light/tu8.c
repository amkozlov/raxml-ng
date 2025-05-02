
#include "header.h"

void predict_unit8(union Entry* data, double* result) {
  unsigned int tmp;
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 4.4603553920224104e-06;
        } else {
          result[0] += 3.166093239189392e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 4.4603553920224104e-06;
          } else {
            result[0] += -0.00010197245417145356;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
              if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.07218104077152019682) ) ) {
                result[0] += -0.002663587202020732;
              } else {
                result[0] += 5.9585153996774e-05;
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01911900000000000405) ) ) {
                  result[0] += 0.00042099986812156864;
                } else {
                  result[0] += 0.0027081297879883483;
                }
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2030091505812350317) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05539262878325219158) ) ) {
                    result[0] += 0.0011310686015590622;
                  } else {
                    result[0] += -0.000711703750059943;
                  }
                } else {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8517455601758795458) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                      result[0] += 0.0006455068163043207;
                    } else {
                      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6208328749497488142) ) ) {
                        result[0] += -0.0008695882031340224;
                      } else {
                        result[0] += -0.00010822750181752809;
                      }
                    }
                  } else {
                    result[0] += 0.0006247131182069239;
                  }
                }
              }
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006028500000000000872) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                    result[0] += 0.00042886182054650845;
                  } else {
                    result[0] += -0.00010822750181752809;
                  }
                } else {
                  result[0] += -0.00010822750181752809;
                }
              } else {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += 5.219048091664662e-07;
                } else {
                  result[0] += -0.000437908063085074;
                }
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                result[0] += -0.00015909258858586058;
              } else {
                result[0] += -0.00014286933599679018;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6750000000000001554) ) ) {
        result[0] += -7.882334611449197e-05;
      } else {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.009719500000000000708) ) ) {
            result[0] += 8.767387563619638e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
              if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4314418144595498217) ) ) {
                result[0] += 9.285855493538397e-05;
              } else {
                result[0] += -0.0015454610201314433;
              }
            } else {
              result[0] += 0.00016905347300155387;
            }
          }
        } else {
          result[0] += 4.86002106209329e-05;
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 6.785350925520938e-05;
      } else {
        result[0] += 6.785350925520938e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          result[0] += 6.785350925520938e-05;
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 6.785350925520938e-05;
          } else {
            result[0] += 6.785350925520938e-05;
          }
        }
      } else {
        result[0] += 6.785350925520938e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 4.272026810853402e-06;
        } else {
          result[0] += 3.0324119974094695e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 4.272026810853402e-06;
          } else {
            result[0] += -9.766689420491402e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            result[0] += -0.00010365783638297208;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -0.00015237525804837326;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  result[0] += -0.00010365783638297208;
                } else {
                  result[0] += -0.00010365783638297208;
                }
              } else {
                result[0] += 4.998685399509248e-07;
              }
            }
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09250981134579591703) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5362694672110553951) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.05721739154190200877) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
                    result[0] += 0.0002272934597209642;
                  } else {
                    result[0] += 5.0709012866339964e-05;
                  }
                } else {
                  result[0] += 0.0010458797338539513;
                }
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.09688331830159578606) ) ) {
                  result[0] += -0.002915673660772057;
                } else {
                  result[0] += -0.00012891238069170842;
                }
              }
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5493276582412061071) ) ) {
                  result[0] += 9.563609067240004e-05;
                } else {
                  result[0] += 0.0009420332513427212;
                }
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5494686760804020631) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01563800000000000259) ) ) {
                    result[0] += -0.00023197548721450928;
                  } else {
                    result[0] += 0.0007901039631447838;
                  }
                } else {
                  if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0004235000000000000483) ) ) {
                    result[0] += 0.0017397647465637843;
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1475515000000000299) ) ) {
                      result[0] += -0.0003946765473253878;
                    } else {
                      result[0] += 0.00027464753053557444;
                    }
                  }
                }
              }
            }
          } else {
            result[0] += -0.0004912989061838292;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5953483130402011936) ) ) {
            result[0] += -8.556611833497024e-05;
          } else {
            result[0] += 0.0024158382170456237;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5531655541959800138) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5499504253266332965) ) ) {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.111039020874343905) ) ) {
                result[0] += -0.0012464706185606445;
              } else {
                result[0] += -0.00014576078270104874;
              }
            } else {
              result[0] += 0.0031725654942336757;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005049500000000001036) ) ) {
              result[0] += -0.0003650688929168473;
            } else {
              result[0] += -0.004022584282840995;
            }
          }
        } else {
          result[0] += -2.158260639233325e-05;
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 6.49885458156985e-05;
      } else {
        result[0] += 6.49885458156985e-05;
      }
    } else {
      result[0] += 6.49885458156985e-05;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 4.091649984952279e-06;
        } else {
          result[0] += 2.9043751485939384e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 4.091649984952279e-06;
          } else {
            result[0] += -9.354312692715585e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01911900000000000405) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.045304313006248043) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.743670590552763966) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4725173572200235816) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5809002386432161602) ) ) {
                      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
                        if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.07218104077152019682) ) ) {
                          result[0] += -0.002479582445547097;
                        } else {
                          result[0] += 0.002157091944764302;
                        }
                      } else {
                        result[0] += 0.00019019989018443035;
                      }
                    } else {
                      result[0] += -0.0004968461927597107;
                    }
                  } else {
                    if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.5642589213209130428) ) ) {
                      result[0] += 0.0008780169435044776;
                    } else {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004302500000000001636) ) ) {
                        result[0] += -0.00018271592541359335;
                      } else {
                        result[0] += 0.000920115465124153;
                      }
                    }
                  }
                } else {
                  result[0] += -9.928111490289247e-05;
                }
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7801862323115579256) ) ) {
                  result[0] += 0.0004852356084948313;
                } else {
                  result[0] += -9.928111490289247e-05;
                }
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7593447680904524821) ) ) {
                result[0] += 0.0005224348205827841;
              } else {
                result[0] += -9.224759024983166e-05;
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -0.00014594155184531247;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  result[0] += -9.928111490289247e-05;
                } else {
                  result[0] += -9.928111490289247e-05;
                }
              } else {
                result[0] += 4.787627031675263e-07;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6750000000000001554) ) ) {
        result[0] += -7.688449153238297e-05;
      } else {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.009719500000000000708) ) ) {
            result[0] += 8.183096610114817e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
              result[0] += 4.7151519215834094e-05;
            } else {
              result[0] += 0.00015977449105502786;
            }
          }
        } else {
          result[0] += 4.774228027053603e-05;
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 6.224454908225427e-05;
      } else {
        result[0] += 6.224454908225427e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 6.224454908225427e-05;
          } else {
            result[0] += 6.224454908225427e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 6.224454908225427e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 6.224454908225427e-05;
            } else {
              result[0] += 6.224454908225427e-05;
            }
          }
        }
      } else {
        result[0] += 6.224454908225427e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 3.918889169147227e-06;
        } else {
          result[0] += 2.7817443708098297e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 3.918889169147227e-06;
          } else {
            result[0] += -8.95934765464235e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08693186820944626136) ) ) {
                result[0] += -0.002341989469709225;
              } else {
                result[0] += 0.005391872775654702;
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01911900000000000405) ) ) {
                  result[0] += 0.00039957003985933873;
                } else {
                  result[0] += 0.002576103107579163;
                }
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1270434093492826821) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05539262878325219158) ) ) {
                    result[0] += 0.0011086666931101462;
                  } else {
                    result[0] += -0.0012233934414970745;
                  }
                } else {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8517455601758795458) ) ) {
                    result[0] += -9.50891907481537e-05;
                  } else {
                    result[0] += 0.0006069046425477762;
                  }
                }
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -0.0001397794945702828;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                    result[0] += 0.0004193227301194126;
                  } else {
                    result[0] += -9.50891907481537e-05;
                  }
                } else {
                  result[0] += -9.50891907481537e-05;
                }
              } else {
                result[0] += 4.5854801337723754e-07;
              }
            }
          }
        }
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004655500000000000783) ) ) {
          result[0] += 0.000129636834382454;
        } else {
          result[0] += 0.0003809609541332666;
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6750000000000001554) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.154253000000000029) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 0.0009488430189122314;
            } else {
              result[0] += -0.00012040442065574786;
            }
          } else {
            result[0] += 0.0008977159525947652;
          }
        } else {
          result[0] += 7.00498294880299e-05;
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 5.961641150489361e-05;
      } else {
        result[0] += 5.961641150489361e-05;
      }
    } else {
      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 5.961641150489361e-05;
            } else {
              result[0] += 5.961641150489361e-05;
            }
          } else {
            result[0] += 5.961641150489361e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 5.961641150489361e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 5.961641150489361e-05;
            } else {
              result[0] += 5.961641150489361e-05;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
          result[0] += -0.0004223479524420715;
        } else {
          result[0] += 5.961641150489361e-05;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 3.7534227943592536e-06;
        } else {
          result[0] += 2.6642914047375654e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 3.7534227943592536e-06;
          } else {
            result[0] += -8.581059136418801e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            result[0] += -9.107426126290742e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -0.00013387761645177596;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  result[0] += -9.107426126290742e-05;
                } else {
                  result[0] += -9.107426126290742e-05;
                }
              } else {
                result[0] += 4.391868438812701e-07;
              }
            }
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09250981134579591703) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5362694672110553951) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.05721739154190200877) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4891798216080402439) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4795216591959799435) ) ) {
                        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4751828078391960308) ) ) {
                          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4737195465326633492) ) ) {
                            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4731110269597990081) ) ) {
                              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4725302343969849939) ) ) {
                                result[0] += 8.184816770339453e-05;
                              } else {
                                result[0] += -0.0009520425049159633;
                              }
                            } else {
                              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005566500000000001135) ) ) {
                                result[0] += 0.00016959453703567246;
                              } else {
                                result[0] += 0.0011215353770027269;
                              }
                            }
                          } else {
                            result[0] += -0.0013075902767071355;
                          }
                        } else {
                          result[0] += 0.001546631627550502;
                        }
                      } else {
                        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06983950000000001268) ) ) {
                          result[0] += -0.0009007913920946917;
                        } else {
                          result[0] += 0.00017604130202579637;
                        }
                      }
                    } else {
                      result[0] += 0.0003126060777132236;
                    }
                  } else {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5321921516834172694) ) ) {
                      result[0] += -0.00024149354073818715;
                    } else {
                      result[0] += 0.00026804717331002886;
                    }
                  }
                } else {
                  result[0] += 0.0010100498747079298;
                }
              } else {
                result[0] += -0.0011871799659310947;
              }
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5493276582412061071) ) ) {
                  result[0] += 8.662455983328885e-05;
                } else {
                  result[0] += 0.0009027828786905373;
                }
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5494686760804020631) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01563800000000000259) ) ) {
                    result[0] += -0.00022050255067022667;
                  } else {
                    result[0] += 0.0007517700717323195;
                  }
                } else {
                  result[0] += -0.00012763673112715975;
                }
              }
            }
          } else {
            result[0] += -0.00047552841283848445;
          }
        } else {
          result[0] += 0.0010769621248145416;
        }
      } else {
        result[0] += -4.4363381622011636e-05;
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 5.7099241188559545e-05;
      } else {
        result[0] += 5.7099241188559545e-05;
      }
    } else {
      result[0] += 5.7099241188559545e-05;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 3.594942869048079e-06;
        } else {
          result[0] += 2.551797628799361e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 3.594942869048079e-06;
          } else {
            result[0] += -8.218743009103157e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            result[0] += -8.722885324108583e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -0.00012822493200386286;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  result[0] += -8.722885324108583e-05;
                } else {
                  result[0] += -8.722885324108583e-05;
                }
              } else {
                result[0] += 4.206431566844642e-07;
              }
            }
          }
        }
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
        result[0] += 0.000332757498637559;
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03643150000000000555) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8254037945979900703) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
                result[0] += -3.722573539584857e-06;
              } else {
                result[0] += -0.0008682540300825254;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002861500000000000328) ) ) {
                result[0] += 0.0009019323617949503;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.394135022639764854) ) ) {
                  result[0] += 0.005455885375064114;
                } else {
                  result[0] += 0.0008090308123446874;
                }
              }
            }
          } else {
            result[0] += -0.0003985790214040853;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9284011333411857914) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.527988611169282529) ) ) {
                result[0] += 0.00011478878736138831;
              } else {
                result[0] += -0.001171077821773873;
              }
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.606193063154585432) ) ) {
                result[0] += 0.0011719771311855304;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8518170160515455835) ) ) {
                  result[0] += 0.00020175482338437474;
                } else {
                  result[0] += 0.0017183835989782578;
                }
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7974125133417085953) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7593447680904524821) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
                  result[0] += 0.0009566120607154401;
                } else {
                  result[0] += -0.00246283407520894;
                }
              } else {
                result[0] += -0.0011173990986461143;
              }
            } else {
              result[0] += 0.0004018279877092715;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 5.468835278758063e-05;
      } else {
        result[0] += 5.468835278758063e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 5.468835278758063e-05;
          } else {
            result[0] += 5.468835278758063e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 5.468835278758063e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 5.468835278758063e-05;
            } else {
              result[0] += 5.468835278758063e-05;
            }
          }
        }
      } else {
        result[0] += 5.468835278758063e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 3.4431544059309367e-06;
        } else {
          result[0] += 2.4440536522270726e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 3.4431544059309367e-06;
          } else {
            result[0] += -7.871724874031368e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7568047583165830039) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01911900000000000405) ) ) {
                result[0] += -0.00010115355175521537;
              } else {
                result[0] += 0.0004968360787469737;
              }
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.013855723816631915) ) ) {
                result[0] += -8.354580901611795e-05;
              } else {
                result[0] += -8.354580901611795e-05;
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -0.00012281091957831275;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  result[0] += -8.354580901611795e-05;
                } else {
                  result[0] += -8.354580901611795e-05;
                }
              } else {
                result[0] += 4.028824354158133e-07;
              }
            }
          }
        }
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
        result[0] += 0.00031870755371526705;
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03643150000000000555) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8254037945979900703) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
                result[0] += -3.5653961554100774e-06;
              } else {
                result[0] += -0.0008315939357160176;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002861500000000000328) ) ) {
                result[0] += 0.0008638502748134858;
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8168185667587940513) ) ) {
                  result[0] += 0.005740479266077433;
                } else {
                  result[0] += 0.0006927965527408152;
                }
              }
            }
          } else {
            result[0] += -0.00038174990915015834;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9284011333411857914) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.527988611169282529) ) ) {
                result[0] += 0.00010994208624502825;
              } else {
                result[0] += -0.0011216316666518825;
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
                result[0] += 0.0009215233739154383;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8518170160515455835) ) ) {
                  result[0] += 2.2653145146215473e-05;
                } else {
                  result[0] += 0.0017355782827885595;
                }
              }
            }
          } else {
            result[0] += -0.00013516871213927384;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 5.237925878458498e-05;
      } else {
        result[0] += 5.237925878458498e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 5.237925878458498e-05;
          } else {
            result[0] += 5.237925878458498e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 5.237925878458498e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 5.237925878458498e-05;
            } else {
              result[0] += 5.237925878458498e-05;
            }
          }
        }
      } else {
        result[0] += 5.237925878458498e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 3.2977748729065937e-06;
        } else {
          result[0] += 2.3408589253117925e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 3.2977748729065937e-06;
          } else {
            result[0] += -7.539358807522289e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            result[0] += -8.00182731379763e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -0.00011762550178007837;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  result[0] += -8.00182731379763e-05;
                } else {
                  result[0] += -8.00182731379763e-05;
                }
              } else {
                result[0] += 3.858716210812704e-07;
              }
            }
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
        result[0] += -7.195782975691979e-05;
      } else {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
              result[0] += 0.00026914723919437494;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.3597967273366834418) ) ) {
                result[0] += -0.0007340012554734835;
              } else {
                if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4612588522637047217) ) ) {
                  result[0] += 0.00019465193684458165;
                } else {
                  result[0] += -0.0007283556128267027;
                }
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4138030768592965147) ) ) {
                  result[0] += 0.0008245339437222832;
                } else {
                  if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4188836135812591954) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4465144967587940106) ) ) {
                      result[0] += 0.00021900331559941477;
                    } else {
                      result[0] += -0.0035639430328305156;
                    }
                  } else {
                    result[0] += 0.0007169353293899277;
                  }
                }
              } else {
                result[0] += 0.00010181709202500447;
              }
            } else {
              result[0] += -0.0012542581214192927;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5180644051256282356) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5012509875628141653) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4914057384422110819) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06607900000000001273) ) ) {
                  result[0] += -0.0008434558850326238;
                } else {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1916738466035730337) ) ) {
                    result[0] += -0.0007079321480535579;
                  } else {
                    result[0] += 0.0002822761719966762;
                  }
                }
              } else {
                result[0] += 0.0007264160849505578;
              }
            } else {
              result[0] += -0.0005444861958326744;
            }
          } else {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.04446937286580055632) ) ) {
              result[0] += 0.0002060160773046615;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5531655541959800138) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02621450000000000516) ) ) {
                    result[0] += -0.0006460911529593377;
                  } else {
                    result[0] += 0.00037224406659082035;
                  }
                } else {
                  result[0] += -0.0030904926306308702;
                }
              } else {
                result[0] += 7.733861583284564e-05;
              }
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 5.016766113763076e-05;
      } else {
        result[0] += 5.016766113763076e-05;
      }
    } else {
      result[0] += 5.016766113763076e-05;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 3.158533667163199e-06;
        } else {
          result[0] += 2.242021366109828e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 3.158533667163199e-06;
          } else {
            result[0] += -7.221026158584903e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            result[0] += -7.663967961275597e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -0.00011265902670969402;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    result[0] += -7.663967961275597e-05;
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                      result[0] += 4.4710022307032825e-05;
                    } else {
                      result[0] += -9.269134719991816e-05;
                    }
                  }
                } else {
                  result[0] += -7.663967961275597e-05;
                }
              } else {
                result[0] += 3.695790505292483e-07;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
        if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09250981134579591703) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5458973873869347182) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5450375474120604524) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.05721739154190200877) ) ) {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
                      result[0] += 0.00030108789444102023;
                    } else {
                      result[0] += 3.590509527552236e-05;
                    }
                  } else {
                    result[0] += 0.0008685255857925773;
                  }
                } else {
                  result[0] += -0.0020886193091454682;
                }
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5531655541959800138) ) ) {
                      result[0] += -0.0010809906582145456;
                    } else {
                      result[0] += 0.0010133950280232476;
                    }
                  } else {
                    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001600500000000000143) ) ) {
                      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05914074587140304151) ) ) {
                        result[0] += -0.002989699684408228;
                      } else {
                        result[0] += 0.0009410967572807097;
                      }
                    } else {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5511625663567840672) ) ) {
                        result[0] += 0.0015750212518110774;
                      } else {
                        result[0] += 0.0005476195694074328;
                      }
                    }
                  }
                } else {
                  result[0] += -0.00012644689038789213;
                }
              }
            } else {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9750000000000000888) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
                  result[0] += -0.0011969023064173317;
                } else {
                  result[0] += 0.005756858860620894;
                }
              } else {
                result[0] += 0.00010134237366361216;
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5953483130402011936) ) ) {
              result[0] += -0.00013535685101401896;
            } else {
              result[0] += 0.0022800385576989;
            }
          }
        } else {
          result[0] += -5.1897684728918966e-05;
        }
      } else {
        result[0] += 0.00017041080132576317;
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 4.8049443280032215e-05;
      } else {
        result[0] += 4.8049443280032215e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        result[0] += 4.8049443280032215e-05;
      } else {
        result[0] += 4.8049443280032215e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 3.02517161149037e-06;
        } else {
          result[0] += 2.1473570029101533e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 3.02517161149037e-06;
          } else {
            result[0] += -6.916134397389632e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7568047583165830039) ) ) {
              result[0] += -2.8307085705395656e-05;
            } else {
              result[0] += -7.340373968103395e-05;
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -0.00010790224999767133;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                      result[0] += 0.0004192882825061087;
                    } else {
                      result[0] += -7.340373968103395e-05;
                    }
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                      result[0] += 4.2822241104625113e-05;
                    } else {
                      result[0] += -8.877766132277361e-05;
                    }
                  }
                } else {
                  result[0] += -7.340373968103395e-05;
                }
              } else {
                result[0] += 3.5397439751427854e-07;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4612588522637047217) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.469327283602055445) ) ) {
            result[0] += 9.316520908768679e-05;
          } else {
            result[0] += 0.0010392249261638063;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4138030768592965147) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.3335138627135679212) ) ) {
              result[0] += 0.0014214386113763882;
            } else {
              result[0] += -0.0006682132013802888;
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4306236034422111225) ) ) {
              result[0] += 0.00036735908014131594;
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4188836135812591954) ) ) {
                result[0] += -0.0027438517653691867;
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                  if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00592850000000000061) ) ) {
                    result[0] += -0.00035152833013708226;
                  } else {
                    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
                      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4632663309547739305) ) ) {
                        result[0] += -0.0008764264388037725;
                      } else {
                        result[0] += 0.001309918560893703;
                      }
                    } else {
                      result[0] += -2.727774576611013e-05;
                    }
                  }
                } else {
                  result[0] += -1.4409822476552561e-05;
                }
              }
            }
          }
        }
      } else {
        result[0] += 0.00016321558444081522;
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 4.6020662457974554e-05;
      } else {
        result[0] += 4.6020662457974554e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 4.6020662457974554e-05;
          } else {
            result[0] += 4.6020662457974554e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 4.6020662457974554e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 4.6020662457974554e-05;
            } else {
              result[0] += 4.6020662457974554e-05;
            }
          }
        }
      } else {
        result[0] += 4.6020662457974554e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 2.8974404718588067e-06;
        } else {
          result[0] += 2.0566896317978232e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 2.8974404718588067e-06;
          } else {
            result[0] += -6.624116012360472e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            result[0] += -7.030443011225997e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -0.00010334631759745286;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  result[0] += -7.030443011225997e-05;
                } else {
                  result[0] += -7.030443011225997e-05;
                }
              } else {
                result[0] += 3.39028616249125e-07;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5493276582412061071) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5012509875628141653) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4891798216080402439) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4795216591959799435) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4751828078391960308) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4737195465326633492) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4731110269597990081) ) ) {
                        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4693702733417085549) ) ) {
                          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4129968667336683663) ) ) {
                            if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4188836135812591954) ) ) {
                              result[0] += 5.523509860629279e-05;
                            } else {
                              result[0] += -0.000900433941010554;
                            }
                          } else {
                            result[0] += 0.00017950737945091492;
                          }
                        } else {
                          result[0] += -0.0008146517251604986;
                        }
                      } else {
                        result[0] += 0.0008778993705493879;
                      }
                    } else {
                      result[0] += -0.0014324667720777833;
                    }
                  } else {
                    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003184500000000000264) ) ) {
                      result[0] += -6.405612763249512e-05;
                    } else {
                      result[0] += 0.002394907107367913;
                    }
                  }
                } else {
                  result[0] += -0.000726516945635901;
                }
              } else {
                result[0] += 0.0004435675769670897;
              }
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4150000000000000355) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1701831610694422292) ) ) {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2328444889043961574) ) ) {
                      result[0] += -0.0015064436590680867;
                    } else {
                      result[0] += 0.001476739857211509;
                    }
                  } else {
                    result[0] += -0.0020112290085595183;
                  }
                } else {
                  result[0] += -3.474918059029313e-05;
                }
              } else {
                result[0] += 8.664093467185848e-05;
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
              result[0] += 0.0008288835643260079;
            } else {
              result[0] += -0.00043516412185218376;
            }
          }
        } else {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.00000001800250948e-35) ) ) {
            result[0] += -0.0009739393300194714;
          } else {
            result[0] += -2.693220352617402e-05;
          }
        }
      } else {
        result[0] += 0.00015632416957791535;
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 4.407754239165295e-05;
      } else {
        result[0] += 4.407754239165295e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        result[0] += 4.407754239165295e-05;
      } else {
        result[0] += 4.407754239165295e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 2.775102495368698e-06;
        } else {
          result[0] += 1.969850488676126e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 2.775102495368698e-06;
          } else {
            result[0] += -6.344427453834855e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7568047583165830039) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01911900000000000405) ) ) {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4725173572200235816) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                    result[0] += -0.00015153232547394726;
                  } else {
                    result[0] += -0.00045466793814643555;
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6852090990703517681) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.679632490452261373) ) ) {
                      result[0] += 0.00047105469317468713;
                    } else {
                      result[0] += 0.0030094699234577333;
                    }
                  } else {
                    result[0] += -6.133967598689503e-05;
                  }
                }
              } else {
                result[0] += 0.00048663646617033777;
              }
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.013855723816631915) ) ) {
                result[0] += -6.73359819933908e-05;
              } else {
                result[0] += -6.73359819933908e-05;
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7418777389447237525) ) ) {
              result[0] += -9.898274930489487e-05;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    result[0] += -6.73359819933908e-05;
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                      result[0] += 4.398261538163522e-05;
                    } else {
                      result[0] += -8.206077400412153e-05;
                    }
                  }
                } else {
                  result[0] += -6.73359819933908e-05;
                }
              } else {
                result[0] += 3.247138873402843e-07;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
          result[0] += 0.0002821092553147104;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8254037945979900703) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
              result[0] += 2.3549154358601364e-06;
            } else {
              result[0] += 0.0013891889643503311;
            }
          } else {
            result[0] += -0.00033524102346497666;
          }
        }
      } else {
        result[0] += 0.00014972372937270613;
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 4.221646624626661e-05;
      } else {
        result[0] += 4.221646624626661e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 4.221646624626661e-05;
            } else {
              result[0] += 4.221646624626661e-05;
            }
          } else {
            result[0] += 4.221646624626661e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 4.221646624626661e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 4.221646624626661e-05;
              } else {
                result[0] += 4.221646624626661e-05;
              }
            } else {
              result[0] += 4.221646624626661e-05;
            }
          }
        }
      } else {
        result[0] += 4.221646624626661e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 2.6579299677073428e-06;
        } else {
          result[0] += 1.886677935136787e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 2.6579299677073428e-06;
          } else {
            result[0] += -6.076548122325223e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7568047583165830039) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5126512388693468258) ) ) {
                  result[0] += -0.0006269161426029499;
                } else {
                  result[0] += -0.002926893059732819;
                }
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01911900000000000405) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.966590843157139501) ) ) {
                    result[0] += -0.00011197611138831605;
                  } else {
                    result[0] += 0.0003644374465088827;
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5525538534170856275) ) ) {
                    result[0] += 0.002869027421639837;
                  } else {
                    result[0] += 0.00027473727159662154;
                  }
                }
              }
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.013855723816631915) ) ) {
                result[0] += -6.44928699908993e-05;
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7801862323115579256) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7782555201758795116) ) ) {
                    result[0] += 7.311619704662505e-05;
                  } else {
                    result[0] += 0.0018005618097570047;
                  }
                } else {
                  result[0] += -6.44928699908993e-05;
                }
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -9.480342297360333e-05;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                      result[0] += 0.0004073963279061104;
                    } else {
                      result[0] += -6.44928699908993e-05;
                    }
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                      result[0] += 4.2125547318014085e-05;
                    } else {
                      result[0] += -7.85959404248361e-05;
                    }
                  }
                } else {
                  result[0] += -6.44928699908993e-05;
                }
              } else {
                result[0] += 3.1100356600623965e-07;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
        if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09250981134579591703) ) ) {
            result[0] += 4.567639435972466e-05;
          } else {
            result[0] += 0.0009481802511946584;
          }
        } else {
          result[0] += -4.64932387072382e-05;
        }
      } else {
        result[0] += 0.00014340197806774786;
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 4.043396989982193e-05;
      } else {
        result[0] += 4.043396989982193e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 4.043396989982193e-05;
          } else {
            result[0] += 4.043396989982193e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 4.043396989982193e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 4.043396989982193e-05;
            } else {
              result[0] += 4.043396989982193e-05;
            }
          }
        }
      } else {
        result[0] += 4.043396989982193e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 2.5457047892921776e-06;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4891798216080402439) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4795216591959799435) ) ) {
              result[0] += 6.166102661898209e-05;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06983950000000001268) ) ) {
                result[0] += -0.0008198262921063961;
              } else {
                result[0] += 0.0001670686985098066;
              }
            }
          } else {
            result[0] += 0.00026792444611534747;
          }
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 2.5457047892921776e-06;
          } else {
            result[0] += -5.8199793994989056e-05;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5068267582412061545) ) ) {
            result[0] += -0.001372644960106683;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1450000000000000455) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9033411549107539518) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8299222285691966183) ) ) {
                    if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
                      result[0] += 2.9834266361159104e-05;
                    } else {
                      result[0] += -0.00043205419367328663;
                    }
                  } else {
                    result[0] += -0.00035308623061425134;
                  }
                } else {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9186477097784532253) ) ) {
                    result[0] += 0.0032350724049862176;
                  } else {
                    if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.966590843157139501) ) ) {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007171500000000001658) ) ) {
                        result[0] += -0.00027466752311680425;
                      } else {
                        result[0] += 0.004554237884569489;
                      }
                    } else {
                      result[0] += 0.0005994388982904104;
                    }
                  }
                }
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.013855723816631915) ) ) {
                  result[0] += -6.176980206617153e-05;
                } else {
                  result[0] += -5.503325234046684e-05;
                }
              }
            } else {
              result[0] += 3.978981501245901e-05;
            }
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += -9.080055939674209e-05;
        } else {
          result[0] += -0.0008807462849765986;
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -5.8199793994989056e-05;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8323869080904523488) ) ) {
                result[0] += 0.00018079340404681356;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.055261500000000012) ) ) {
                  result[0] += -6.176980206617153e-05;
                } else {
                  result[0] += 0.0001523458892790908;
                }
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -6.176980206617153e-05;
              } else {
                result[0] += 0.000702453587529928;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0005965000000000001334) ) ) {
            result[0] += 2.978721324820834e-07;
          } else {
            result[0] += -0.0003241878065433061;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 3.872673549516323e-05;
      } else {
        result[0] += 3.872673549516323e-05;
      }
    } else {
      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
        result[0] += 3.872673549516323e-05;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
          result[0] += -0.00042288775565949086;
        } else {
          result[0] += 3.872673549516323e-05;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5126512388693468258) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 2.438218069310162e-06;
        } else {
          result[0] += -1.4220263030250422e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 2.438218069310162e-06;
          } else {
            result[0] += -5.5742437200728185e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
              result[0] += -0.0027970372406725136;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
                result[0] += 0.0005975361376363822;
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1270434093492826821) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05539262878325219158) ) ) {
                    result[0] += 0.0011266011411780557;
                  } else {
                    result[0] += -0.0011392943827108868;
                  }
                } else {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                    result[0] += -9.774601178900271e-06;
                  } else {
                    if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.992027305872230758) ) ) {
                      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9774026691300493619) ) ) {
                        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7640286906783920751) ) ) {
                          result[0] += -5.916170962514806e-05;
                        } else {
                          result[0] += -5.916170962514806e-05;
                        }
                      } else {
                        result[0] += -0.0006150212514487718;
                      }
                    } else {
                      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                        result[0] += 0.0002753284539394733;
                      } else {
                        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7968587857286433263) ) ) {
                          result[0] += -0.00015540273747691145;
                        } else {
                          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7990273242713569202) ) ) {
                            result[0] += 0.0005223420415287627;
                          } else {
                            result[0] += -5.916170962514806e-05;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -8.696670782717326e-05;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  result[0] += -5.916170962514806e-05;
                } else {
                  result[0] += -5.916170962514806e-05;
                }
              } else {
                result[0] += 2.852951445181941e-07;
              }
            }
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
        result[0] += -6.876051078859798e-05;
      } else {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
          result[0] += 8.748171925254317e-05;
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5180644051256282356) ) ) {
            result[0] += -0.00022640747545797508;
          } else {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.04446937286580055632) ) ) {
              result[0] += 0.0001914484215721828;
            } else {
              result[0] += 1.9033308070346057e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 3.7091585264272567e-05;
      } else {
        result[0] += 3.7091585264272567e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 3.7091585264272567e-05;
          } else {
            result[0] += 3.7091585264272567e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 3.7091585264272567e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 3.7091585264272567e-05;
            } else {
              result[0] += 3.7091585264272567e-05;
            }
          }
        }
      } else {
        result[0] += 3.7091585264272567e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5126512388693468258) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 2.3352697368981376e-06;
        } else {
          result[0] += -1.3619844066970941e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 2.3352697368981376e-06;
          } else {
            result[0] += -5.3388836828952614e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
              result[0] += -0.00267893856720025;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
                result[0] += 0.0005723065038723248;
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8517455601758795458) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7568047583165830039) ) ) {
                    if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1270434093492826821) ) ) {
                      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05539262878325219158) ) ) {
                        result[0] += 0.0010790329149239508;
                      } else {
                        result[0] += -0.0010911902125782765;
                      }
                    } else {
                      result[0] += -9.361890394731006e-06;
                    }
                  } else {
                    if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.013855723816631915) ) ) {
                      result[0] += -5.666373808387487e-05;
                    } else {
                      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7801862323115579256) ) ) {
                        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
                          result[0] += 0.0009072488767199646;
                        } else {
                          result[0] += -0.00036162994979630603;
                        }
                      } else {
                        result[0] += -5.666373808387487e-05;
                      }
                    }
                  }
                } else {
                  result[0] += 0.000615405531867943;
                }
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -8.329473210897738e-05;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                      result[0] += 0.0003850592968655285;
                    } else {
                      result[0] += -5.666373808387487e-05;
                    }
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                      result[0] += 4.5452953803296386e-05;
                    } else {
                      result[0] += -7.017133775113236e-05;
                    }
                  }
                } else {
                  result[0] += -5.666373808387487e-05;
                }
              } else {
                result[0] += 2.732491918845511e-07;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
        result[0] += 5.106696883720094e-06;
      } else {
        result[0] += 0.00013884523605777466;
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 3.5525475613316664e-05;
      } else {
        result[0] += 3.5525475613316664e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 3.5525475613316664e-05;
            } else {
              result[0] += 3.5525475613316664e-05;
            }
          } else {
            result[0] += 3.5525475613316664e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 3.5525475613316664e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 3.5525475613316664e-05;
              } else {
                result[0] += 3.5525475613316664e-05;
              }
            } else {
              result[0] += 3.5525475613316664e-05;
            }
          }
        }
      } else {
        result[0] += 3.5525475613316664e-05;
      }
    }
  }
}

