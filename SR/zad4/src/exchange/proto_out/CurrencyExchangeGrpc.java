package exchange.proto_out;

import static io.grpc.MethodDescriptor.generateFullMethodName;
import static io.grpc.stub.ClientCalls.asyncServerStreamingCall;
import static io.grpc.stub.ClientCalls.blockingServerStreamingCall;
import static io.grpc.stub.ServerCalls.asyncServerStreamingCall;
import static io.grpc.stub.ServerCalls.asyncUnimplementedUnaryCall;

/**
 *
 */
@javax.annotation.Generated(
        value = "by gRPC proto compiler (version 1.17.1)",
        comments = "Source: exchange.proto")
public final class CurrencyExchangeGrpc {

    private CurrencyExchangeGrpc() {
    }

    public static final String SERVICE_NAME = "CurrencyExchange";

    // Static method descriptors that strictly reflect the proto.
    private static volatile io.grpc.MethodDescriptor<exchange.proto_out.CurrencyArguments,
            exchange.proto_out.CurrencyResult> getGetValueMethod;

    @io.grpc.stub.annotations.RpcMethod(
            fullMethodName = SERVICE_NAME + '/' + "GetValue",
            requestType = exchange.proto_out.CurrencyArguments.class,
            responseType = exchange.proto_out.CurrencyResult.class,
            methodType = io.grpc.MethodDescriptor.MethodType.SERVER_STREAMING)
    public static io.grpc.MethodDescriptor<exchange.proto_out.CurrencyArguments,
            exchange.proto_out.CurrencyResult> getGetValueMethod() {
        io.grpc.MethodDescriptor<exchange.proto_out.CurrencyArguments, exchange.proto_out.CurrencyResult> getGetValueMethod;
        if ((getGetValueMethod = CurrencyExchangeGrpc.getGetValueMethod) == null) {
            synchronized (CurrencyExchangeGrpc.class) {
                if ((getGetValueMethod = CurrencyExchangeGrpc.getGetValueMethod) == null) {
                    CurrencyExchangeGrpc.getGetValueMethod = getGetValueMethod =
                            io.grpc.MethodDescriptor.<exchange.proto_out.CurrencyArguments, exchange.proto_out.CurrencyResult>newBuilder()
                                    .setType(io.grpc.MethodDescriptor.MethodType.SERVER_STREAMING)
                                    .setFullMethodName(generateFullMethodName(
                                            "CurrencyExchange", "GetValue"))
                                    .setSampledToLocalTracing(true)
                                    .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                                            exchange.proto_out.CurrencyArguments.getDefaultInstance()))
                                    .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                                            exchange.proto_out.CurrencyResult.getDefaultInstance()))
                                    .setSchemaDescriptor(new CurrencyExchangeMethodDescriptorSupplier("GetValue"))
                                    .build();
                }
            }
        }
        return getGetValueMethod;
    }

    /**
     * Creates a new async stub that supports all call types for the service
     */
    public static CurrencyExchangeStub newStub(io.grpc.Channel channel) {
        return new CurrencyExchangeStub(channel);
    }

    /**
     * Creates a new blocking-style stub that supports unary and streaming output calls on the service
     */
    public static CurrencyExchangeBlockingStub newBlockingStub(
            io.grpc.Channel channel) {
        return new CurrencyExchangeBlockingStub(channel);
    }

    /**
     * Creates a new ListenableFuture-style stub that supports unary calls on the service
     */
    public static CurrencyExchangeFutureStub newFutureStub(
            io.grpc.Channel channel) {
        return new CurrencyExchangeFutureStub(channel);
    }

    /**
     *
     */
    public static abstract class CurrencyExchangeImplBase implements io.grpc.BindableService {

        /**
         *
         */
        public void getValue(exchange.proto_out.CurrencyArguments request,
                             io.grpc.stub.StreamObserver<exchange.proto_out.CurrencyResult> responseObserver) {
            asyncUnimplementedUnaryCall(getGetValueMethod(), responseObserver);
        }

        @java.lang.Override
        public final io.grpc.ServerServiceDefinition bindService() {
            return io.grpc.ServerServiceDefinition.builder(getServiceDescriptor())
                    .addMethod(
                            getGetValueMethod(),
                            asyncServerStreamingCall(
                                    new MethodHandlers<
                                            exchange.proto_out.CurrencyArguments,
                                            exchange.proto_out.CurrencyResult>(
                                            this, METHODID_GET_VALUE)))
                    .build();
        }
    }

    /**
     *
     */
    public static final class CurrencyExchangeStub extends io.grpc.stub.AbstractStub<CurrencyExchangeStub> {
        private CurrencyExchangeStub(io.grpc.Channel channel) {
            super(channel);
        }

        private CurrencyExchangeStub(io.grpc.Channel channel,
                                     io.grpc.CallOptions callOptions) {
            super(channel, callOptions);
        }

        @java.lang.Override
        protected CurrencyExchangeStub build(io.grpc.Channel channel,
                                             io.grpc.CallOptions callOptions) {
            return new CurrencyExchangeStub(channel, callOptions);
        }

        /**
         *
         */
        public void getValue(exchange.proto_out.CurrencyArguments request,
                             io.grpc.stub.StreamObserver<exchange.proto_out.CurrencyResult> responseObserver) {
            asyncServerStreamingCall(
                    getChannel().newCall(getGetValueMethod(), getCallOptions()), request, responseObserver);
        }
    }

    /**
     *
     */
    public static final class CurrencyExchangeBlockingStub extends io.grpc.stub.AbstractStub<CurrencyExchangeBlockingStub> {
        private CurrencyExchangeBlockingStub(io.grpc.Channel channel) {
            super(channel);
        }

        private CurrencyExchangeBlockingStub(io.grpc.Channel channel,
                                             io.grpc.CallOptions callOptions) {
            super(channel, callOptions);
        }

        @java.lang.Override
        protected CurrencyExchangeBlockingStub build(io.grpc.Channel channel,
                                                     io.grpc.CallOptions callOptions) {
            return new CurrencyExchangeBlockingStub(channel, callOptions);
        }

        /**
         *
         */
        public java.util.Iterator<exchange.proto_out.CurrencyResult> getValue(
                exchange.proto_out.CurrencyArguments request) {
            return blockingServerStreamingCall(
                    getChannel(), getGetValueMethod(), getCallOptions(), request);
        }
    }

    /**
     *
     */
    public static final class CurrencyExchangeFutureStub extends io.grpc.stub.AbstractStub<CurrencyExchangeFutureStub> {
        private CurrencyExchangeFutureStub(io.grpc.Channel channel) {
            super(channel);
        }

        private CurrencyExchangeFutureStub(io.grpc.Channel channel,
                                           io.grpc.CallOptions callOptions) {
            super(channel, callOptions);
        }

        @java.lang.Override
        protected CurrencyExchangeFutureStub build(io.grpc.Channel channel,
                                                   io.grpc.CallOptions callOptions) {
            return new CurrencyExchangeFutureStub(channel, callOptions);
        }
    }

    private static final int METHODID_GET_VALUE = 0;

    private static final class MethodHandlers<Req, Resp> implements
            io.grpc.stub.ServerCalls.UnaryMethod<Req, Resp>,
            io.grpc.stub.ServerCalls.ServerStreamingMethod<Req, Resp>,
            io.grpc.stub.ServerCalls.ClientStreamingMethod<Req, Resp>,
            io.grpc.stub.ServerCalls.BidiStreamingMethod<Req, Resp> {
        private final CurrencyExchangeImplBase serviceImpl;
        private final int methodId;

        MethodHandlers(CurrencyExchangeImplBase serviceImpl, int methodId) {
            this.serviceImpl = serviceImpl;
            this.methodId = methodId;
        }

        @java.lang.Override
        @java.lang.SuppressWarnings("unchecked")
        public void invoke(Req request, io.grpc.stub.StreamObserver<Resp> responseObserver) {
            switch (methodId) {
                case METHODID_GET_VALUE:
                    serviceImpl.getValue((exchange.proto_out.CurrencyArguments) request,
                            (io.grpc.stub.StreamObserver<exchange.proto_out.CurrencyResult>) responseObserver);
                    break;
                default:
                    throw new AssertionError();
            }
        }

        @java.lang.Override
        @java.lang.SuppressWarnings("unchecked")
        public io.grpc.stub.StreamObserver<Req> invoke(
                io.grpc.stub.StreamObserver<Resp> responseObserver) {
            switch (methodId) {
                default:
                    throw new AssertionError();
            }
        }
    }

    private static abstract class CurrencyExchangeBaseDescriptorSupplier
            implements io.grpc.protobuf.ProtoFileDescriptorSupplier, io.grpc.protobuf.ProtoServiceDescriptorSupplier {
        CurrencyExchangeBaseDescriptorSupplier() {
        }

        @java.lang.Override
        public com.google.protobuf.Descriptors.FileDescriptor getFileDescriptor() {
            return exchange.proto_out.CurrencyProto.getDescriptor();
        }

        @java.lang.Override
        public com.google.protobuf.Descriptors.ServiceDescriptor getServiceDescriptor() {
            return getFileDescriptor().findServiceByName("CurrencyExchange");
        }
    }

    private static final class CurrencyExchangeFileDescriptorSupplier
            extends CurrencyExchangeBaseDescriptorSupplier {
        CurrencyExchangeFileDescriptorSupplier() {
        }
    }

    private static final class CurrencyExchangeMethodDescriptorSupplier
            extends CurrencyExchangeBaseDescriptorSupplier
            implements io.grpc.protobuf.ProtoMethodDescriptorSupplier {
        private final String methodName;

        CurrencyExchangeMethodDescriptorSupplier(String methodName) {
            this.methodName = methodName;
        }

        @java.lang.Override
        public com.google.protobuf.Descriptors.MethodDescriptor getMethodDescriptor() {
            return getServiceDescriptor().findMethodByName(methodName);
        }
    }

    private static volatile io.grpc.ServiceDescriptor serviceDescriptor;

    public static io.grpc.ServiceDescriptor getServiceDescriptor() {
        io.grpc.ServiceDescriptor result = serviceDescriptor;
        if (result == null) {
            synchronized (CurrencyExchangeGrpc.class) {
                result = serviceDescriptor;
                if (result == null) {
                    serviceDescriptor = result = io.grpc.ServiceDescriptor.newBuilder(SERVICE_NAME)
                            .setSchemaDescriptor(new CurrencyExchangeFileDescriptorSupplier())
                            .addMethod(getGetValueMethod())
                            .build();
                }
            }
        }
        return result;
    }
}
