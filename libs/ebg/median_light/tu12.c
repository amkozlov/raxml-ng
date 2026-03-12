
#include "header.h"

void predict_unit12(union Entry* data, double* result) {
  unsigned int tmp;
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 2.8203164276005465e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -6.44779535229022e-06;
        } else {
          result[0] += -6.44779535229022e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8643464628140704598) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8168185667587940513) ) ) {
            result[0] += 8.241612408634084e-07;
          } else {
            result[0] += -2.691056914832147e-05;
          }
        } else {
          result[0] += 0.0009482043550157032;
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
            result[0] += -1.005954462509043e-05;
          } else {
            result[0] += -0.0006527591870882579;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  result[0] += -6.843306742777078e-06;
                } else {
                  result[0] += -6.843306742777078e-06;
                }
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                    result[0] += 0.0005300711758580847;
                  } else {
                    result[0] += 9.837074869611656e-06;
                  }
                } else {
                  result[0] += -9.04972288252216e-06;
                }
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.598708736933611707) ) ) {
                  result[0] += -1.1569141262042608e-05;
                } else {
                  if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9250000000000001554) ) ) {
                    result[0] += 0.0020202142080179954;
                  } else {
                    result[0] += -0.0001998776595533187;
                  }
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.96280210579579717) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.055261500000000012) ) ) {
                    result[0] += -0.000808125550431394;
                  } else {
                    result[0] += 0.00011257867733127015;
                  }
                } else {
                  result[0] += 4.909753735784546e-05;
                }
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
              result[0] += 3.820008590483834e-07;
            } else {
              result[0] += -0.0024787856951619517;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 4.2904286767157436e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 4.2904286767157436e-06;
          } else {
            result[0] += 4.2904286767157436e-06;
          }
        } else {
          result[0] += 4.2904286767157436e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 4.2904286767157436e-06;
            } else {
              result[0] += 4.2904286767157436e-06;
            }
          } else {
            result[0] += 4.2904286767157436e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 4.2904286767157436e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 4.2904286767157436e-06;
              } else {
                result[0] += 4.2904286767157436e-06;
              }
            } else {
              result[0] += 4.2904286767157436e-06;
            }
          }
        }
      } else {
        result[0] += 4.2904286767157436e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 2.701234842261368e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -6.175551541284304e-06;
        } else {
          result[0] += -6.175551541284304e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8643464628140704598) ) ) {
          result[0] += -2.4071819691761165e-06;
        } else {
          result[0] += 0.0009081685360857225;
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
            result[0] += -9.634802737966834e-06;
          } else {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
              result[0] += 0.0012425126052022545;
            } else {
              result[0] += -0.0038737273479560966;
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  result[0] += -6.5543633434065885e-06;
                } else {
                  result[0] += -6.5543633434065885e-06;
                }
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                    result[0] += 0.0005076900999809287;
                  } else {
                    result[0] += 9.421726272869644e-06;
                  }
                } else {
                  result[0] += -8.667618471405886e-06;
                }
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.598708736933611707) ) ) {
                  result[0] += -1.1080660016104098e-05;
                } else {
                  if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9550000000000000711) ) ) {
                    if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.04500000000000000527) ) ) {
                      result[0] += 0.00022626375698305107;
                    } else {
                      result[0] += 0.0028790190781955104;
                    }
                  } else {
                    result[0] += -0.0003383381128012672;
                  }
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.96280210579579717) ) ) {
                  result[0] += -0.0007230997089361342;
                } else {
                  result[0] += 4.702450309559069e-05;
                }
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
              result[0] += 3.6587172280991414e-07;
            } else {
              result[0] += -0.002374124485020086;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 4.109274872978766e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 4.109274872978766e-06;
          } else {
            result[0] += 4.109274872978766e-06;
          }
        } else {
          result[0] += 4.109274872978766e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 4.109274872978766e-06;
            } else {
              result[0] += 4.109274872978766e-06;
            }
          } else {
            result[0] += 4.109274872978766e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 4.109274872978766e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 4.109274872978766e-06;
              } else {
                result[0] += 4.109274872978766e-06;
              }
            } else {
              result[0] += 4.109274872978766e-06;
            }
          }
        }
      } else {
        result[0] += 4.109274872978766e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 2.587181211880747e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -5.914802619396569e-06;
        } else {
          result[0] += -5.914802619396569e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9189305784170854752) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4612588522637047217) ) ) {
              if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.469327283602055445) ) ) {
                result[0] += 4.300162488006179e-05;
              } else {
                result[0] += 0.001062633659490285;
              }
            } else {
              result[0] += -7.54650040313394e-06;
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
                result[0] += -9.227994631884114e-06;
              } else {
                result[0] += -0.000499011858582831;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    result[0] += -6.277619936112721e-06;
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                        result[0] += 0.0004862540152299323;
                      } else {
                        result[0] += 9.023914846384259e-06;
                      }
                    } else {
                      result[0] += -8.301647568783722e-06;
                    }
                  }
                } else {
                  result[0] += -3.425307139824625e-05;
                }
              } else {
                if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.03500000000000001027) ) ) {
                  if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02310400000000000301) ) ) {
                    result[0] += 3.504236034582842e-07;
                  } else {
                    result[0] += 3.504236034582842e-07;
                  }
                } else {
                  result[0] += -0.003941927792592312;
                }
              }
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0006325000000000001411) ) ) {
            result[0] += 2.845134742121686e-08;
          } else {
            result[0] += -5.1259751578437105e-05;
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)4.143697683123688691) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -6.277619936112721e-06;
          } else {
            result[0] += -0.0004367591744763893;
          }
        } else {
          result[0] += 2.845134742121686e-08;
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 3.935769885497976e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 3.935769885497976e-06;
          } else {
            result[0] += 3.935769885497976e-06;
          }
        } else {
          result[0] += 3.935769885497976e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 3.935769885497976e-06;
            } else {
              result[0] += 3.935769885497976e-06;
            }
          } else {
            result[0] += 3.935769885497976e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 3.935769885497976e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 3.935769885497976e-06;
              } else {
                result[0] += 3.935769885497976e-06;
              }
            } else {
              result[0] += 3.935769885497976e-06;
            }
          }
        }
      } else {
        result[0] += 3.935769885497976e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 2.477943242248701e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -5.665063240512528e-06;
        } else {
          result[0] += -5.665063240512528e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9189305784170854752) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            result[0] += -1.6190110446701353e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
                result[0] += -8.83836309284438e-06;
              } else {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.0650000000000000161) ) ) {
                  result[0] += 0.001211119940626834;
                } else {
                  result[0] += -0.003240013065209065;
                }
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    result[0] += -6.0125614033776705e-06;
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                        result[0] += 0.0004657230214576043;
                      } else {
                        result[0] += 8.642900122165424e-06;
                      }
                    } else {
                      result[0] += -7.951128973160065e-06;
                    }
                  }
                } else {
                  result[0] += -3.2806811678976226e-05;
                }
              } else {
                if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.03500000000000001027) ) ) {
                  if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02310400000000000301) ) ) {
                    result[0] += 3.356277465708573e-07;
                  } else {
                    result[0] += 3.356277465708573e-07;
                  }
                } else {
                  result[0] += -0.0037754886631952843;
                }
              }
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0006325000000000001411) ) ) {
            result[0] += 2.7250052586781147e-08;
          } else {
            result[0] += -4.909542263211401e-05;
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)4.143697683123688691) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -6.0125614033776705e-06;
          } else {
            result[0] += -0.00041831799021811305;
          }
        } else {
          result[0] += 2.7250052586781147e-08;
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 3.7695907600276194e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 3.7695907600276194e-06;
            } else {
              result[0] += 3.7695907600276194e-06;
            }
          } else {
            result[0] += 3.7695907600276194e-06;
          }
        } else {
          result[0] += 3.7695907600276194e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 3.7695907600276194e-06;
            } else {
              result[0] += 3.7695907600276194e-06;
            }
          } else {
            result[0] += 3.7695907600276194e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 3.7695907600276194e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 3.7695907600276194e-06;
              } else {
                result[0] += 3.7695907600276194e-06;
              }
            } else {
              result[0] += 3.7695907600276194e-06;
            }
          }
        }
      } else {
        result[0] += 3.7695907600276194e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 2.3733176028065936e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -5.425868551177578e-06;
        } else {
          result[0] += -5.425868551177578e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8643464628140704598) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8168185667587940513) ) ) {
            result[0] += 1.1145230197369511e-06;
          } else {
            result[0] += -2.5285699020116024e-05;
          }
        } else {
          result[0] += 0.0008702101338473016;
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
            result[0] += -8.465182878525828e-06;
          } else {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
              result[0] += 0.0011599830961386837;
            } else {
              result[0] += -0.00355229582330817;
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  result[0] += -5.758694377374575e-06;
                } else {
                  result[0] += -5.758694377374575e-06;
                }
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                    result[0] += 0.00044605890321139423;
                  } else {
                    result[0] += 8.277972896836246e-06;
                  }
                } else {
                  result[0] += -7.615410245256639e-06;
                }
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.598708736933611707) ) ) {
                  result[0] += -7.781349463662161e-06;
                } else {
                  if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9250000000000001554) ) ) {
                    if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.04500000000000000527) ) ) {
                      result[0] += 0.0002195417276705619;
                    } else {
                      result[0] += 0.0042482855408700485;
                    }
                  } else {
                    result[0] += -0.0001743212418724582;
                  }
                }
              } else {
                result[0] += -0.00034081625482428957;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
              result[0] += 3.2145661181650806e-07;
            } else {
              result[0] += -0.0030039640345749805;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 3.6104281783451927e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 3.6104281783451927e-06;
          } else {
            result[0] += 3.6104281783451927e-06;
          }
        } else {
          result[0] += 3.6104281783451927e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 3.6104281783451927e-06;
            } else {
              result[0] += 3.6104281783451927e-06;
            }
          } else {
            result[0] += 3.6104281783451927e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 3.6104281783451927e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 3.6104281783451927e-06;
              } else {
                result[0] += 3.6104281783451927e-06;
              }
            } else {
              result[0] += 3.6104281783451927e-06;
            }
          }
        }
      } else {
        result[0] += 3.6104281783451927e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 2.2731095481749445e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -5.196773325339679e-06;
        } else {
          result[0] += -5.196773325339679e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8643464628140704598) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8168185667587940513) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                result[0] += -5.1903392939432315e-06;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002547500000000000285) ) ) {
                  result[0] += 0.0005748766517187961;
                } else {
                  result[0] += 0.004749450319897628;
                }
              }
            } else {
              result[0] += -2.4218066645161795e-05;
            }
          } else {
            result[0] += 0.0008334674473520807;
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7418777389447237525) ) ) {
                  result[0] += -0.00021852442641528922;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -5.515546321635209e-06;
                  } else {
                    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006671500000000001214) ) ) {
                      result[0] += 0.0008564011786848472;
                    } else {
                      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.555383890033505745) ) ) {
                        result[0] += -9.818736261810366e-06;
                      } else {
                        result[0] += -0.00035863475232915116;
                      }
                    }
                  }
                }
              } else {
                result[0] += -5.515546321635209e-06;
              }
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                result[0] += 7.928453911554285e-06;
              } else {
                result[0] += -7.293866493591876e-06;
              }
            }
          } else {
            result[0] += -8.96050842672525e-05;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -8.10775936834988e-06;
          } else {
            result[0] += -0.00020903485667174304;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
            result[0] += 3.078838216933096e-07;
          } else {
            result[0] += -0.002877128337687228;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 3.457985882502478e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 3.457985882502478e-06;
          } else {
            result[0] += 3.457985882502478e-06;
          }
        } else {
          result[0] += 3.457985882502478e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 3.457985882502478e-06;
            } else {
              result[0] += 3.457985882502478e-06;
            }
          } else {
            result[0] += 3.457985882502478e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 3.457985882502478e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 3.457985882502478e-06;
              } else {
                result[0] += 3.457985882502478e-06;
              }
            } else {
              result[0] += 3.457985882502478e-06;
            }
          }
        }
      } else {
        result[0] += 3.457985882502478e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9189305784170854752) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
          result[0] += 2.177132555665452e-07;
        } else {
          result[0] += -4.977351135626123e-06;
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
            result[0] += 3.6062297673832388e-06;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.07127303416489440269) ) ) {
                result[0] += -6.759573595338175e-05;
              } else {
                result[0] += -2.0182815094874643e-05;
              }
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007599500000000001219) ) ) {
                result[0] += 4.255064876604241e-05;
              } else {
                result[0] += -2.3556585553702513e-05;
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
              result[0] += -7.765427270546198e-06;
            } else {
              result[0] += -0.0004722692935235715;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -5.282664651492224e-06;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                      result[0] += 0.0003910654245097886;
                    } else {
                      result[0] += 7.593692587670227e-06;
                    }
                  } else {
                    result[0] += -6.9858992113365e-06;
                  }
                }
              } else {
                result[0] += -1.3248033795899306e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.03500000000000001027) ) ) {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02310400000000000301) ) ) {
                  result[0] += 2.9488411243065844e-07;
                } else {
                  result[0] += 2.9488411243065844e-07;
                }
              } else {
                result[0] += -0.0033677610169624574;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -5.282664651492224e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          result[0] += 0.0016566172437400464;
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0005965000000000001334) ) ) {
            result[0] += -0.001195254899071489;
          } else {
            result[0] += 0.00013932005196576588;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 3.3119801233821468e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 3.3119801233821468e-06;
          } else {
            result[0] += 3.3119801233821468e-06;
          }
        } else {
          result[0] += 3.3119801233821468e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 3.3119801233821468e-06;
            } else {
              result[0] += 3.3119801233821468e-06;
            }
          } else {
            result[0] += 3.3119801233821468e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 3.3119801233821468e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 3.3119801233821468e-06;
              } else {
                result[0] += 3.3119801233821468e-06;
              }
            } else {
              result[0] += 3.3119801233821468e-06;
            }
          }
        }
      } else {
        result[0] += 3.3119801233821468e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 2.085207978095331e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -4.767193559611258e-06;
        } else {
          result[0] += -4.767193559611258e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8517455601758795458) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8490362337185931585) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
                result[0] += 3.4539647400996728e-06;
              } else {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
                  result[0] += -6.380173949723295e-05;
                } else {
                  result[0] += -1.1704592023520232e-05;
                }
              }
            } else {
              result[0] += -1.9802517120792084e-05;
            }
          } else {
            result[0] += 0.0005053687778177339;
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7418777389447237525) ) ) {
                  result[0] += -0.00020896984088745975;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -5.0596158916587485e-06;
                  } else {
                    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006671500000000001214) ) ) {
                      result[0] += 0.0008037296772489868;
                    } else {
                      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.555383890033505745) ) ) {
                        result[0] += -9.181113212141905e-06;
                      } else {
                        result[0] += -0.00034326914919240745;
                      }
                    }
                  }
                }
              } else {
                result[0] += -5.0596158916587485e-06;
              }
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                result[0] += 7.273065815770547e-06;
              } else {
                result[0] += -6.690935162280289e-06;
              }
            }
          } else {
            result[0] += -8.526234022755531e-05;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -7.437549383809036e-06;
          } else {
            result[0] += -0.00019988094710998174;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
            result[0] += 2.8243328696444715e-07;
          } else {
            result[0] += -0.0019485690039788637;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 3.172139132547393e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 3.172139132547393e-06;
          } else {
            result[0] += 3.172139132547393e-06;
          }
        } else {
          result[0] += 3.172139132547393e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 3.172139132547393e-06;
            } else {
              result[0] += 3.172139132547393e-06;
            }
          } else {
            result[0] += 3.172139132547393e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 3.172139132547393e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 3.172139132547393e-06;
              } else {
                result[0] += 3.172139132547393e-06;
              }
            } else {
              result[0] += 3.172139132547393e-06;
            }
          }
        }
      } else {
        result[0] += 3.172139132547393e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.9971647112608742e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -4.565909419597328e-06;
        } else {
          result[0] += -4.565909419597328e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
              result[0] += 3.3081287647704106e-06;
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.07127303416489440269) ) ) {
                  result[0] += -6.204776994039811e-05;
                } else {
                  result[0] += -1.6636754161089987e-05;
                }
              } else {
                result[0] += -1.121039167058696e-05;
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7418777389447237525) ) ) {
                  result[0] += -0.00020014655435925273;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -4.845984869377324e-06;
                  } else {
                    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006671500000000001214) ) ) {
                      result[0] += 0.0007697939801001802;
                    } else {
                      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.555383890033505745) ) ) {
                        result[0] += -8.793461136729464e-06;
                      } else {
                        result[0] += -0.0003287753732161431;
                      }
                    }
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 6.965976795850151e-06;
                } else {
                  result[0] += -6.408425313836427e-06;
                }
              }
            } else {
              result[0] += -3.950034180208441e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -4.845984869377324e-06;
          } else {
            result[0] += -0.0003847643272552941;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -7.123515411239866e-06;
          } else {
            result[0] += -0.00019144141889676681;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
            result[0] += 2.705081698977568e-07;
          } else {
            result[0] += -0.0025311777907178912;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 3.0382026163720594e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 3.0382026163720594e-06;
          } else {
            result[0] += 3.0382026163720594e-06;
          }
        } else {
          result[0] += 3.0382026163720594e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 3.0382026163720594e-06;
            } else {
              result[0] += 3.0382026163720594e-06;
            }
          } else {
            result[0] += 3.0382026163720594e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 3.0382026163720594e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 3.0382026163720594e-06;
              } else {
                result[0] += 3.0382026163720594e-06;
              }
            } else {
              result[0] += 3.0382026163720594e-06;
            }
          }
        }
      } else {
        result[0] += 3.0382026163720594e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.912838875452778e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -4.373124054494633e-06;
        } else {
          result[0] += -4.373124054494633e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003120500000000000444) ) ) {
                result[0] += -2.3633292049926698e-05;
              } else {
                result[0] += 3.87940848641165e-05;
              }
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.07127303416489440269) ) ) {
                  result[0] += -5.942794092442192e-05;
                } else {
                  result[0] += -1.5934304237023707e-05;
                }
              } else {
                result[0] += -1.0737057827850246e-05;
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.00019169581147097112;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -4.641373941636326e-06;
                  } else {
                    result[0] += -7.391845367066616e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 6.671853926456152e-06;
                } else {
                  result[0] += -6.137843815097359e-06;
                }
              }
            } else {
              result[0] += -3.7832527766327934e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -4.641373941636326e-06;
          } else {
            result[0] += -0.000368518509721105;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -6.82274082436866e-06;
          } else {
            result[0] += -0.00018335823098257226;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
            result[0] += 2.590865643632328e-07;
          } else {
            result[0] += -0.002424304440924963;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.9099212715559154e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 2.9099212715559154e-06;
            } else {
              result[0] += 2.9099212715559154e-06;
            }
          } else {
            result[0] += 2.9099212715559154e-06;
          }
        } else {
          result[0] += 2.9099212715559154e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 2.9099212715559154e-06;
            } else {
              result[0] += 2.9099212715559154e-06;
            }
          } else {
            result[0] += 2.9099212715559154e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 2.9099212715559154e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 2.9099212715559154e-06;
              } else {
                result[0] += 2.9099212715559154e-06;
              }
            } else {
              result[0] += 2.9099212715559154e-06;
            }
          }
        }
      } else {
        result[0] += 2.9099212715559154e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.8320735104184923e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -4.188478622444093e-06;
        } else {
          result[0] += -4.188478622444093e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5012509875628141653) ) ) {
              result[0] += 3.993290667744743e-05;
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1701831610694422292) ) ) {
                  result[0] += 0.00012151230960625482;
                } else {
                  if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4150000000000000355) ) ) {
                    result[0] += -0.0017051670217314195;
                  } else {
                    result[0] += -0.0001263597702182857;
                  }
                }
              } else {
                result[0] += -4.552207287384489e-06;
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.00018360188239640953;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -4.445402255015455e-06;
                  } else {
                    result[0] += -7.079741144903034e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 6.390149740735073e-06;
                } else {
                  result[0] += -5.878687018039966e-06;
                }
              }
            } else {
              result[0] += -3.623513346698335e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -4.445402255015455e-06;
          } else {
            result[0] += -0.0003529586356818253;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -6.534665775139331e-06;
          } else {
            result[0] += -0.0001756163376912065;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
            result[0] += 2.48147210706852e-07;
          } else {
            result[0] += -0.002321943580510636;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.7870563210687962e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 2.7870563210687962e-06;
            } else {
              result[0] += 2.7870563210687962e-06;
            }
          } else {
            result[0] += 2.7870563210687962e-06;
          }
        } else {
          result[0] += 2.7870563210687962e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 2.7870563210687962e-06;
            } else {
              result[0] += 2.7870563210687962e-06;
            }
          } else {
            result[0] += 2.7870563210687962e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 2.7870563210687962e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 2.7870563210687962e-06;
              } else {
                result[0] += 2.7870563210687962e-06;
              }
            } else {
              result[0] += 2.7870563210687962e-06;
            }
          }
        }
      } else {
        result[0] += 2.7870563210687962e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.7547182832024734e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -4.011629432885693e-06;
        } else {
          result[0] += -4.011629432885693e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003120500000000000444) ) ) {
                result[0] += -2.244322205926419e-05;
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                  result[0] += 3.164453994777622e-05;
                } else {
                  result[0] += 0.0012183437122779335;
                }
              }
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.0141436144428988015) ) ) {
                  result[0] += -6.361065654002048e-05;
                } else {
                  result[0] += -2.024201915937607e-05;
                }
              } else {
                result[0] += -1.0091502630296085e-05;
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.0001758497014662718;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -4.257705036782598e-06;
                  } else {
                    result[0] += -6.780814829020654e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 6.12033988740309e-06;
                } else {
                  result[0] += -5.6304725400581815e-06;
                }
              }
            } else {
              result[0] += -3.470518558737906e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -4.257705036782598e-06;
          } else {
            result[0] += -0.0003380557426997564;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -6.258754053834183e-06;
          } else {
            result[0] += -0.00016820132861667522;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
            result[0] += 2.37669746916175e-07;
          } else {
            result[0] += -0.002223904679652165;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.66937906971733e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 2.66937906971733e-06;
          } else {
            result[0] += 2.66937906971733e-06;
          }
        } else {
          result[0] += 2.66937906971733e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 2.66937906971733e-06;
            } else {
              result[0] += 2.66937906971733e-06;
            }
          } else {
            result[0] += 2.66937906971733e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 2.66937906971733e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 2.66937906971733e-06;
              } else {
                result[0] += 2.66937906971733e-06;
              }
            } else {
              result[0] += 2.66937906971733e-06;
            }
          }
        }
      } else {
        result[0] += 2.66937906971733e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.680629208323069e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -3.842247306828548e-06;
        } else {
          result[0] += -3.842247306828548e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4612588522637047217) ) ) {
              if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.6027691365924101596) ) ) {
                result[0] += -2.564627774931015e-05;
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0008435000000000001741) ) ) {
                  result[0] += -0.0005799605197981989;
                } else {
                  if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4702452205161443133) ) ) {
                    result[0] += 0.00012477376928541185;
                  } else {
                    result[0] += 0.0006660493411609167;
                  }
                }
              }
            } else {
              result[0] += -7.456813632588365e-06;
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.00016842483912562345;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -4.0779329159225625e-06;
                  } else {
                    result[0] += -6.49451001165045e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 5.861922154742548e-06;
                } else {
                  result[0] += -5.392738366078075e-06;
                }
              }
            } else {
              result[0] += -3.323983635252504e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -4.0779329159225625e-06;
          } else {
            result[0] += -0.0003237820912116825;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -5.99449209099766e-06;
          } else {
            result[0] += -0.00016109940180031096;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
            result[0] += 2.2763467071942752e-07;
          } else {
            result[0] += -0.0021300052532246027;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.5566704784482798e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 2.5566704784482798e-06;
            } else {
              result[0] += 2.5566704784482798e-06;
            }
          } else {
            result[0] += 2.5566704784482798e-06;
          }
        } else {
          result[0] += 2.5566704784482798e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 2.5566704784482798e-06;
            } else {
              result[0] += 2.5566704784482798e-06;
            }
          } else {
            result[0] += 2.5566704784482798e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 2.5566704784482798e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 2.5566704784482798e-06;
              } else {
                result[0] += 2.5566704784482798e-06;
              }
            } else {
              result[0] += 2.5566704784482798e-06;
            }
          }
        }
      } else {
        result[0] += 2.5566704784482798e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.6096683797667235e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -3.6800169641321846e-06;
        } else {
          result[0] += -3.6800169641321846e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
              result[0] += 3.0828996843129845e-06;
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.0141436144428988015) ) ) {
                  result[0] += -6.031406014065121e-05;
                } else {
                  result[0] += -1.9072497580656687e-05;
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008191000000000002099) ) ) {
                  result[0] += 4.3108070304939945e-05;
                } else {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.038794232605861678) ) ) {
                    result[0] += -3.882508749571736e-05;
                  } else {
                    result[0] += -1.8035296821158173e-05;
                  }
                }
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.00016131347507537824;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -3.9057512728338415e-06;
                  } else {
                    result[0] += -6.22029377810333e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 5.614415535808037e-06;
                } else {
                  result[0] += -5.165041988584125e-06;
                }
              }
            } else {
              result[0] += -3.1836358228392e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -3.9057512728338415e-06;
          } else {
            result[0] += -0.00031011111289571986;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -5.741388001501667e-06;
          } else {
            result[0] += -0.00015429733804043857;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
            result[0] += 2.1802330328486447e-07;
          } else {
            result[0] += -0.002040070521131334;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.4487207566431596e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 2.4487207566431596e-06;
          } else {
            result[0] += 2.4487207566431596e-06;
          }
        } else {
          result[0] += 2.4487207566431596e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 2.4487207566431596e-06;
            } else {
              result[0] += 2.4487207566431596e-06;
            }
          } else {
            result[0] += 2.4487207566431596e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 2.4487207566431596e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 2.4487207566431596e-06;
              } else {
                result[0] += 2.4487207566431596e-06;
              }
            } else {
              result[0] += 2.4487207566431596e-06;
            }
          }
        }
      } else {
        result[0] += 2.4487207566431596e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.5417037142926513e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -3.5246364366584272e-06;
        } else {
          result[0] += -3.5246364366584272e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.3075945000000000484) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7847910031909549611) ) ) {
                  result[0] += 5.803440095317882e-06;
                } else {
                  result[0] += -2.229815442821893e-05;
                }
              } else {
                result[0] += 0.00011682594486129282;
              }
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.02463433988323724885) ) ) {
                  result[0] += -5.246565249520075e-05;
                } else {
                  result[0] += -1.8647142492244884e-05;
                }
              } else {
                result[0] += -8.589063749085189e-06;
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.00015450237254782567;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -3.740839616483003e-06;
                  } else {
                    result[0] += -5.957655714827075e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 5.377359333102072e-06;
                } else {
                  result[0] += -4.9469595839559816e-06;
                }
              }
            } else {
              result[0] += -3.0492138845007007e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -3.740839616483003e-06;
          } else {
            result[0] += -0.0002970173612182533;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -5.498970668973091e-06;
          } else {
            result[0] += -0.00014778247628675814;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
            result[0] += 2.0881775445284652e-07;
          } else {
            result[0] += -0.001953933082976398;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.3453289716306643e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 2.3453289716306643e-06;
          } else {
            result[0] += 2.3453289716306643e-06;
          }
        } else {
          result[0] += 2.3453289716306643e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 2.3453289716306643e-06;
            } else {
              result[0] += 2.3453289716306643e-06;
            }
          } else {
            result[0] += 2.3453289716306643e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 2.3453289716306643e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 2.3453289716306643e-06;
              } else {
                result[0] += 2.3453289716306643e-06;
              }
            } else {
              result[0] += 2.3453289716306643e-06;
            }
          }
        }
      } else {
        result[0] += 2.3453289716306643e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.476608705582141e-07;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.629563023060444982) ) ) {
          result[0] += -3.3758165062018533e-06;
        } else {
          result[0] += -3.3758165062018533e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
              result[0] += 2.540102683052293e-06;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01173150000000000061) ) ) {
                result[0] += 2.0181667073532323e-05;
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                  if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5008047942959380494) ) ) {
                    result[0] += -2.0779982154095393e-05;
                  } else {
                    result[0] += -9.561423757488092e-05;
                  }
                } else {
                  result[0] += -1.6911142441058895e-05;
                }
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
                  result[0] += -0.00014797885366831708;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -3.5828909878573393e-06;
                  } else {
                    result[0] += -5.706106959345951e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += 5.150312301053847e-06;
                } else {
                  result[0] += -4.738085223582563e-06;
                }
              }
            } else {
              result[0] += -2.9204676133905544e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
            result[0] += -3.5828909878573393e-06;
          } else {
            result[0] += -0.0002844764640689272;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -5.266788868879338e-06;
          } else {
            result[0] += -0.000141542690073645;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
            result[0] += 2.0000088943591578e-07;
          } else {
            result[0] += -0.0018714326064730533;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.2463026746715702e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 2.2463026746715702e-06;
            } else {
              result[0] += 2.2463026746715702e-06;
            }
          } else {
            result[0] += 2.2463026746715702e-06;
          }
        } else {
          result[0] += 2.2463026746715702e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 2.2463026746715702e-06;
            } else {
              result[0] += 2.2463026746715702e-06;
            }
          } else {
            result[0] += 2.2463026746715702e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 2.2463026746715702e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 2.2463026746715702e-06;
              } else {
                result[0] += 2.2463026746715702e-06;
              }
            } else {
              result[0] += 2.2463026746715702e-06;
            }
          }
        }
      } else {
        result[0] += 2.2463026746715702e-06;
      }
    }
  }
}

