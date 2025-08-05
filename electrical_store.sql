--
-- PostgreSQL database dump
--

-- Dumped from database version 16.2
-- Dumped by pg_dump version 16.2

-- Started on 2024-11-16 15:44:27

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 228 (class 1255 OID 16696)
-- Name: count_orders_by_month(integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.count_orders_by_month(input_month integer) RETURNS integer
    LANGUAGE plpgsql
    AS $$
DECLARE
    total_orders integer;
BEGIN
    SELECT COUNT(*)
    INTO total_orders
    FROM zakaz
    WHERE EXTRACT(MONTH FROM "Дата") = input_month;

    RETURN total_orders;
END;
$$;


ALTER FUNCTION public.count_orders_by_month(input_month integer) OWNER TO postgres;

--
-- TOC entry 227 (class 1255 OID 16695)
-- Name: count_orders_by_year_month(); Type: PROCEDURE; Schema: public; Owner: postgres
--

CREATE PROCEDURE public.count_orders_by_year_month()
    LANGUAGE plpgsql
    AS $$
DECLARE
    year_month_record RECORD;
BEGIN
    FOR year_month_record IN
        SELECT DATE_TRUNC('month', Дата) AS year_month, COUNT(*) AS total_orders
        FROM zakaz
        GROUP BY DATE_TRUNC('month', Дата)
    LOOP
        RAISE NOTICE 'Год-месяц: %, Количество заказов: %',
  year_month_record.year_month, year_month_record.total_orders;
    END LOOP;
END;
$$;


ALTER PROCEDURE public.count_orders_by_year_month() OWNER TO postgres;

--
-- TOC entry 247 (class 1255 OID 17146)
-- Name: get__order_status(integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.get__order_status(order_number integer) RETURNS TABLE("Номер" integer, "Статус" text, "Дата" date)
    LANGUAGE plpgsql
    AS $$
BEGIN
    RETURN QUERY
    SELECT z.Номер, s.Статус, s.Дата
    FROM zakaz z
	join status_zakaza s on
	z.Номер = s.Номер
  where z.Номер = order_number
  group by z.Номер, s.Статус, s.Дата;
END;
$$;


ALTER FUNCTION public.get__order_status(order_number integer) OWNER TO postgres;

--
-- TOC entry 230 (class 1255 OID 16701)
-- Name: get_order_delivery_by_month(integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.get_order_delivery_by_month(input_month integer) RETURNS TABLE(order_number integer, delivery_method text)
    LANGUAGE plpgsql
    AS $$
BEGIN
    RETURN QUERY
    SELECT "Номер", "Способ получения"
    FROM zakaz
    WHERE EXTRACT(MONTH FROM "Дата") = input_month;
END;
$$;


ALTER FUNCTION public.get_order_delivery_by_month(input_month integer) OWNER TO postgres;

--
-- TOC entry 244 (class 1255 OID 16724)
-- Name: get_order_status(integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.get_order_status(order_number integer) RETURNS TABLE("Номер" integer, "Статус" text)
    LANGUAGE plpgsql
    AS $$
BEGIN
    RETURN QUERY
    SELECT z.Номер, s.Статус
    FROM zakaz z
	join status_zakaza s on
	z.Номер = s.Номер
  where z.Номер = order_number
  group by z.Номер, s.Статус, s.Дата;
END;
$$;


ALTER FUNCTION public.get_order_status(order_number integer) OWNER TO postgres;

--
-- TOC entry 246 (class 1255 OID 17171)
-- Name: get_order_statuses(integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.get_order_statuses(order_number integer) RETURNS TABLE(status text, date timestamp without time zone)
    LANGUAGE plpgsql
    AS $$
BEGIN
  RETURN QUERY
    SELECT
      status,
      date
    FROM status_zakaza
    WHERE
      "Номер" = order_number;
END;
$$;


ALTER FUNCTION public.get_order_statuses(order_number integer) OWNER TO postgres;

--
-- TOC entry 253 (class 1255 OID 17175)
-- Name: get_order_statusess(integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.get_order_statusess(order_number integer) RETURNS TABLE("номер_заказа" integer, "статус" character varying, "дата_изменения_статуса" date)
    LANGUAGE plpgsql
    AS $$
BEGIN
    RETURN QUERY
    SELECT
        з.Номер,
        с.Статус,
        с.Дата
    FROM zakaz з
    LEFT JOIN status_zakaza с ON з.Номер = с.Номер
    WHERE з.номер = get_order_statuses.order_number
    ORDER BY с.дата_изменения_статуса DESC;
END;
$$;


ALTER FUNCTION public.get_order_statusess(order_number integer) OWNER TO postgres;

--
-- TOC entry 243 (class 1255 OID 16752)
-- Name: get_order_sum(date); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.get_order_sum(input_month date) RETURNS TABLE(month_name date, kolvo bigint, summa double precision)
    LANGUAGE plpgsql
    AS $$
BEGIN
    RETURN QUERY
    SELECT "Дата" AS month_name, 
       COUNT(DISTINCT z."Номер"),
SUM(t."Количество товаров" * t."Сумма")
FROM zakaz z
JOIN "Товар в поставке/заказе" t ON z."Номер" = t."Номер заказа/поставки"
and "Тип операции(заказ/поставка)" = 'Заказ'
    GROUP BY "Дата"
ORDER BY month_name;
END;
$$;


ALTER FUNCTION public.get_order_sum(input_month date) OWNER TO postgres;

--
-- TOC entry 245 (class 1255 OID 17156)
-- Name: get_order_summary(date); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.get_order_summary(input_date date) RETURNS TABLE(month1 date, month date, "Кол-во заказов" bigint, "Сумма заказов" money)
    LANGUAGE plpgsql
    AS $$
BEGIN
    RETURN QUERY
	select
	DATE_TRUNC('month', input_date)::date as month1,
    DATE_TRUNC('month', "Дата")::date AS month_year,
        COUNT(DISTINCT z."Номер") AS total_orders,
        SUM(t."Количество товаров" * t."Стоимость единицы товара")
    FROM zakaz z
    JOIN "Товар в поставке/заказе" t ON z."Номер" = t."Номер заказа/поставки"
    AND t."Тип операции(заказ/поставка)" = 'Заказ'
	WHERE DATE_TRUNC('month', input_date)::date = DATE_TRUNC('month', "Дата")::date
    GROUP BY
	month_year,
        month
    ORDER BY
        month;
END;
$$;


ALTER FUNCTION public.get_order_summary(input_date date) OWNER TO postgres;

--
-- TOC entry 252 (class 1255 OID 17174)
-- Name: get_orderr_statuses(integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.get_orderr_statuses(order_number integer) RETURNS TABLE("номер_заказа" integer, "статус" character varying, "дата_изменения_статуса" date)
    LANGUAGE plpgsql
    AS $$
BEGIN
    RETURN QUERY
    SELECT
        з.номер_заказа,
        с.статус,
        с.дата_изменения_статуса
    FROM zakaz з
    JOIN status_zakaza с ON з.номер = с.номер
    WHERE з.номер = get_order_statuses.order_number
    ORDER BY с.дата_изменения_статуса DESC;
END;
$$;


ALTER FUNCTION public.get_orderr_statuses(order_number integer) OWNER TO postgres;

--
-- TOC entry 248 (class 1255 OID 17157)
-- Name: get_sezon(date); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.get_sezon(input_date date) RETURNS TABLE(month date, "Категория товаров" text, "Кол-во проданных товаров" bigint, "Сумма проданных товаров" money)
    LANGUAGE plpgsql
    AS $$
BEGIN
    RETURN QUERY
	select  DATE_TRUNC('month', "Дата")::date as month,
"tovar-katalog"."Тип товара" as "Категория товаров",
sum("Товар в поставке/заказе"."Количество товаров") as "Кол-во проданных товаров",
sum("Товар в поставке/заказе"."Количество товаров"*"Товар в поставке/заказе"."Стоимость единицы товара")
as "Сумма проданных товаров"
from "tovar-katalog"
left join "Товар в поставке/заказе"
on "tovar-katalog".Артикул="Товар в поставке/заказе".Артикул
join zakaz
on zakaz.Номер = "Товар в поставке/заказе"."Номер заказа/поставки"
where "Товар в поставке/заказе"."Тип операции(заказ/поставка)" = 'Заказ' and
DATE_TRUNC('month', "Дата")::date = DATE_TRUNC('month', input_date)::date
GROUP BY DATE_TRUNC('month', "Дата"),"tovar-katalog"."Тип товара"
ORDER BY  month;
END;
$$;


ALTER FUNCTION public.get_sezon(input_date date) OWNER TO postgres;

--
-- TOC entry 250 (class 1255 OID 16706)
-- Name: get_total_orders_by_month(date); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.get_total_orders_by_month(input_month date) RETURNS TABLE(month_name date, total_orders bigint)
    LANGUAGE plpgsql
    AS $$
BEGIN
    RETURN QUERY
    SELECT ("Дата", 'Month') AS month_name, COUNT(*) AS total_orders
    FROM zakaz
    WHERE EXTRACT(MONTH FROM "Дата") = input_month
    GROUP BY ("Дата", 'Month');
END;
$$;


ALTER FUNCTION public.get_total_orders_by_month(input_month date) OWNER TO postgres;

--
-- TOC entry 242 (class 1255 OID 16705)
-- Name: get_total_orders_by_month(integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.get_total_orders_by_month(input_month integer) RETURNS TABLE(month_name text, total_orders bigint)
    LANGUAGE plpgsql
    AS $$
BEGIN
    RETURN QUERY
    SELECT TO_CHAR("Дата", 'Month') AS month_name, COUNT(*) AS total_orders
    FROM zakaz
    WHERE EXTRACT(MONTH FROM "Дата") = input_month
    GROUP BY TO_CHAR("Дата", 'Month');
END;
$$;


ALTER FUNCTION public.get_total_orders_by_month(input_month integer) OWNER TO postgres;

--
-- TOC entry 249 (class 1255 OID 17172)
-- Name: gett_order_statuses(integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.gett_order_statuses(order_number integer) RETURNS TABLE(status text, date timestamp without time zone)
    LANGUAGE plpgsql
    AS $$
BEGIN
  RETURN QUERY
    SELECT
      status,
      date
    FROM status_zakaza
    WHERE
      "Номер" = order_number
    ORDER BY
      date;
END;
$$;


ALTER FUNCTION public.gett_order_statuses(order_number integer) OWNER TO postgres;

--
-- TOC entry 251 (class 1255 OID 17173)
-- Name: gettt_order_statuses(integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.gettt_order_statuses(order_number integer) RETURNS TABLE(status text, data date)
    LANGUAGE plpgsql
    AS $$
BEGIN
  RETURN QUERY
    SELECT
      status,
      data
    FROM status_zakaza
    WHERE
      "Номер" = order_number
    ORDER BY
      data;
END;
$$;


ALTER FUNCTION public.gettt_order_statuses(order_number integer) OWNER TO postgres;

--
-- TOC entry 229 (class 1255 OID 16700)
-- Name: Кол-во заказов за месяц(integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public."Кол-во заказов за месяц"(input_month integer) RETURNS text
    LANGUAGE plpgsql
    AS $$
DECLARE
    total_orders text;
BEGIN
    SELECT "Способ получения"
    INTO total_orders
    FROM zakaz
    WHERE EXTRACT(MONTH FROM "Дата") = input_month;
    RETURN total_orders;
END;
$$;


ALTER FUNCTION public."Кол-во заказов за месяц"(input_month integer) OWNER TO postgres;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 218 (class 1259 OID 16498)
-- Name: garantiya; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.garantiya (
    "Код" integer NOT NULL,
    "Тип_товара" character(35) NOT NULL,
    "Срок_гарантии" character(35) NOT NULL,
    "Условия гарантии" text NOT NULL
);


ALTER TABLE public.garantiya OWNER TO postgres;

--
-- TOC entry 215 (class 1259 OID 16419)
-- Name: klient; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.klient (
    "Код" integer NOT NULL,
    "ФИО" text NOT NULL,
    "Телефон" text NOT NULL,
    "Адрес электронной почты" text NOT NULL,
    "Адрес проживания" text NOT NULL
);


ALTER TABLE public.klient OWNER TO postgres;

--
-- TOC entry 220 (class 1259 OID 17080)
-- Name: zakaz; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.zakaz (
    "Номер" integer NOT NULL,
    "Способ получения" text NOT NULL,
    "Дата" date NOT NULL,
    "Клиент" integer NOT NULL,
    "Сотрудник" integer NOT NULL
);


ALTER TABLE public.zakaz OWNER TO postgres;

--
-- TOC entry 226 (class 1259 OID 17167)
-- Name: klient_v; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW public.klient_v AS
 SELECT z."Дата",
    z."Способ получения",
    k."ФИО",
    k."Адрес электронной почты"
   FROM (public.zakaz z
     RIGHT JOIN public.klient k ON ((z."Клиент" = k."Код")))
  GROUP BY z."Дата", z."Способ получения", k."ФИО", k."Адрес электронной почты";


ALTER VIEW public.klient_v OWNER TO postgres;

--
-- TOC entry 219 (class 1259 OID 16510)
-- Name: postavshik; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.postavshik (
    "Код" integer NOT NULL,
    "Название" text NOT NULL
);


ALTER TABLE public.postavshik OWNER TO postgres;

--
-- TOC entry 216 (class 1259 OID 16426)
-- Name: sotrudnik_magazina; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.sotrudnik_magazina (
    "Код" integer NOT NULL,
    "ФИО" name NOT NULL,
    "Номер_телефона" text NOT NULL,
    "Должность" text NOT NULL
);


ALTER TABLE public.sotrudnik_magazina OWNER TO postgres;

--
-- TOC entry 221 (class 1259 OID 17087)
-- Name: status_zakaza; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.status_zakaza (
    "Номер" integer NOT NULL,
    "Статус" text NOT NULL,
    "Дата" date NOT NULL
);


ALTER TABLE public.status_zakaza OWNER TO postgres;

--
-- TOC entry 217 (class 1259 OID 16486)
-- Name: tovar-katalog; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."tovar-katalog" (
    "Артикул" text NOT NULL,
    "Название" text NOT NULL,
    "Тип товара" text NOT NULL,
    "Гарантия" integer NOT NULL
);


ALTER TABLE public."tovar-katalog" OWNER TO postgres;

--
-- TOC entry 222 (class 1259 OID 17094)
-- Name: Товар в поставке/заказе; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Товар в поставке/заказе" (
    "ID" integer NOT NULL,
    "Количество товаров" integer NOT NULL,
    "Стоимость единицы товара" money NOT NULL,
    "Артикул" text NOT NULL,
    "Номер заказа/поставки" integer NOT NULL,
    "Тип операции(заказ/поставка)" text NOT NULL
);


ALTER TABLE public."Товар в поставке/заказе" OWNER TO postgres;

--
-- TOC entry 224 (class 1259 OID 17158)
-- Name: tovary_v; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW public.tovary_v AS
 SELECT "tovar-katalog"."Артикул",
    "tovar-katalog"."Тип товара" AS "Категория товаров",
    "tovar-katalog"."Название" AS "Название товара",
    "Товар в поставке/заказе"."Количество товаров" AS "Кол-во проданных товаров",
    "Товар в поставке/заказе"."Стоимость единицы товара",
    "Товар в поставке/заказе"."Тип операции(заказ/поставка)"
   FROM (public."tovar-katalog"
     LEFT JOIN public."Товар в поставке/заказе" ON (("tovar-katalog"."Артикул" = "Товар в поставке/заказе"."Артикул")))
  GROUP BY "tovar-katalog"."Тип товара", "Товар в поставке/заказе"."Количество товаров", "Товар в поставке/заказе"."Стоимость единицы товара", "tovar-katalog"."Название", "tovar-katalog"."Артикул", "Товар в поставке/заказе"."Тип операции(заказ/поставка)";


ALTER VIEW public.tovary_v OWNER TO postgres;

--
-- TOC entry 225 (class 1259 OID 17163)
-- Name: zakaz_v; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW public.zakaz_v AS
 SELECT "Номер" AS "Номер заказа",
    "Дата" AS "Дата оформления заказа",
    "Способ получения"
   FROM public.zakaz;


ALTER VIEW public.zakaz_v OWNER TO postgres;

--
-- TOC entry 223 (class 1259 OID 17101)
-- Name: Поставка; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Поставка" (
    "Код" integer NOT NULL,
    "Дата" date NOT NULL,
    "Сотрудник" integer NOT NULL,
    "Поставщик" integer NOT NULL
);


ALTER TABLE public."Поставка" OWNER TO postgres;

--
-- TOC entry 4923 (class 0 OID 16498)
-- Dependencies: 218
-- Data for Name: garantiya; Type: TABLE DATA; Schema: public; Owner: postgres
--

INSERT INTO public.garantiya ("Код", "Тип_товара", "Срок_гарантии", "Условия гарантии") VALUES (1, 'бытовые светильники                ', '6 месяцев                          ', 'самопроизвольное перегорание');
INSERT INTO public.garantiya ("Код", "Тип_товара", "Срок_гарантии", "Условия гарантии") VALUES (2, 'электромеханические инструменты    ', '12 месяцев                         ', 'самопроизвольная поломка');
INSERT INTO public.garantiya ("Код", "Тип_товара", "Срок_гарантии", "Условия гарантии") VALUES (3, 'контрольно-измерительные приборы   ', '24 месяца                          ', 'неверные показания');
INSERT INTO public.garantiya ("Код", "Тип_товара", "Срок_гарантии", "Условия гарантии") VALUES (4, 'компьютерные комплектующие         ', '6 месяцев                          ', 'брак');


--
-- TOC entry 4920 (class 0 OID 16419)
-- Dependencies: 215
-- Data for Name: klient; Type: TABLE DATA; Schema: public; Owner: postgres
--

INSERT INTO public.klient ("Код", "ФИО", "Телефон", "Адрес электронной почты", "Адрес проживания") VALUES (1, 'Никанор Артурович Владимиров', '+7 (740) 451-4723', 'Taisiya.Kalashnikova30@mail.ru', 'ал. Проточная, 808');
INSERT INTO public.klient ("Код", "ФИО", "Телефон", "Адрес электронной почты", "Адрес проживания") VALUES (2, 'Архипов Мина Демьянович', '+7 (369) 497-8589', 'Marian_Matveev@hotmail.com', 'Локомотивная пл., 860');
INSERT INTO public.klient ("Код", "ФИО", "Телефон", "Адрес электронной почты", "Адрес проживания") VALUES (3, 'Севастьян Вишняков', '+7 (126) 386-0023', 'Zosima.Safonov53@yandex.ru', 'ал. Санаторная, 989');
INSERT INTO public.klient ("Код", "ФИО", "Телефон", "Адрес электронной почты", "Адрес проживания") VALUES (4, 'Алла Сергеева', '+7 (816) 563-6655', 'Glafira.Borisova@hotmail.com', 'Лесозаводская аллея, 849');
INSERT INTO public.klient ("Код", "ФИО", "Телефон", "Адрес электронной почты", "Адрес проживания") VALUES (6, 'Моисеев Аскольд', '+7 (940) 370-8580', 'Agafon.Naumov@yandex.ru', 'Ольховая ал., 126');
INSERT INTO public.klient ("Код", "ФИО", "Телефон", "Адрес электронной почты", "Адрес проживания") VALUES (7, 'Щербаков Прохор', '+7 (395) 769-0621', 'Fadei.Eliseev@yahoo.com', 'Инженерная аллея, 487');
INSERT INTO public.klient ("Код", "ФИО", "Телефон", "Адрес электронной почты", "Адрес проживания") VALUES (8, 'Осипов Панкрат', '+7 (854) 751-7894', 'Klavdiya.Kryukova@hotmail.com', 'аллея Лесозаводская, 202');
INSERT INTO public.klient ("Код", "ФИО", "Телефон", "Адрес электронной почты", "Адрес проживания") VALUES (9, 'Мамонтов Парамон', '+7 (469) 667-5008', 'Maiya_Romanova@yandex.ru', 'наб. Тихая, 255');
INSERT INTO public.klient ("Код", "ФИО", "Телефон", "Адрес электронной почты", "Адрес проживания") VALUES (5, 'Широков Владимир Иванович', '+7-963-932-21-01', 'shirok789p2gmail.com', 'Tula');


--
-- TOC entry 4924 (class 0 OID 16510)
-- Dependencies: 219
-- Data for Name: postavshik; Type: TABLE DATA; Schema: public; Owner: postgres
--

INSERT INTO public.postavshik ("Код", "Название") VALUES (8, 'ПАО Дроздов');
INSERT INTO public.postavshik ("Код", "Название") VALUES (9, 'ЗАО ПромТоргИнкорпорэйтед');
INSERT INTO public.postavshik ("Код", "Название") VALUES (1, 'АО Петров');
INSERT INTO public.postavshik ("Код", "Название") VALUES (3, 'ИП Моржов');
INSERT INTO public.postavshik ("Код", "Название") VALUES (5, 'ИП Смирнова');
INSERT INTO public.postavshik ("Код", "Название") VALUES (4, 'ИП Алексеев');
INSERT INTO public.postavshik ("Код", "Название") VALUES (6, 'ИП Максимов');
INSERT INTO public.postavshik ("Код", "Название") VALUES (7, 'АО Промторг');
INSERT INTO public.postavshik ("Код", "Название") VALUES (10, 'АО "Торговый дом"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (11, 'ООО "Снабжение"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (12, 'ИП Иванов');
INSERT INTO public.postavshik ("Код", "Название") VALUES (13, 'ЗАО "Металлснаб"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (14, 'ООО "Промстрой"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (15, 'ИП Соколов');
INSERT INTO public.postavshik ("Код", "Название") VALUES (16, 'АО "Энергоснаб"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (17, 'ООО "Стройматериалы"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (18, 'ИП Кузнецов');
INSERT INTO public.postavshik ("Код", "Название") VALUES (19, 'ЗАО "Торговый дом"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (20, 'ООО "Металлпром"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (21, 'ИП Васильев');
INSERT INTO public.postavshik ("Код", "Название") VALUES (22, 'АО "Промышленник"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (23, 'ООО "Стройиндустрия"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (24, 'ИП Михайлов');
INSERT INTO public.postavshik ("Код", "Название") VALUES (25, 'ЗАО "Торговый дом"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (26, 'ООО "Энергоснаб"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (27, 'ИП Николаев');
INSERT INTO public.postavshik ("Код", "Название") VALUES (28, 'АО "Промышленник"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (29, 'ООО "Промстрой"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (30, 'ИП Сидоров');
INSERT INTO public.postavshik ("Код", "Название") VALUES (31, 'ЗАО "Торговый дом"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (32, 'ООО "Стройматериалы"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (33, 'ИП Андреев');
INSERT INTO public.postavshik ("Код", "Название") VALUES (34, 'АО "Энергоснаб"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (35, 'ООО "Промстрой"');
INSERT INTO public.postavshik ("Код", "Название") VALUES (36, 'ИП Павлов');
INSERT INTO public.postavshik ("Код", "Название") VALUES (2, 'ИП Петрович');


--
-- TOC entry 4921 (class 0 OID 16426)
-- Dependencies: 216
-- Data for Name: sotrudnik_magazina; Type: TABLE DATA; Schema: public; Owner: postgres
--

INSERT INTO public.sotrudnik_magazina ("Код", "ФИО", "Номер_телефона", "Должность") VALUES (1, 'Галактион Селиверстов', '+7 (726) 766-4138', 'менеджер');
INSERT INTO public.sotrudnik_magazina ("Код", "ФИО", "Номер_телефона", "Должность") VALUES (2, 'Радим Иосифович Суворов', '+7 (010) 215-9362', 'администратор');
INSERT INTO public.sotrudnik_magazina ("Код", "ФИО", "Номер_телефона", "Должность") VALUES (4, 'Жданов Геннадий Игнатьевич', '+7 (335) 400-7361', 'координатор');
INSERT INTO public.sotrudnik_magazina ("Код", "ФИО", "Номер_телефона", "Должность") VALUES (5, 'Валентина Наумовна Антонова', '+7 (970) 037-4816', 'консультант');
INSERT INTO public.sotrudnik_magazina ("Код", "ФИО", "Номер_телефона", "Должность") VALUES (6, 'Сергеев Карп Гавриилович', '+7 (963) 554-4295', 'сотрудник');
INSERT INTO public.sotrudnik_magazina ("Код", "ФИО", "Номер_телефона", "Должность") VALUES (7, 'Марфа Петрова', '+7 (820) 623-9454', 'разработчик');
INSERT INTO public.sotrudnik_magazina ("Код", "ФИО", "Номер_телефона", "Должность") VALUES (8, 'Агафья Захаровна Соловьева', '+7 (365) 315-2949', 'агент');
INSERT INTO public.sotrudnik_magazina ("Код", "ФИО", "Номер_телефона", "Должность") VALUES (9, 'Зинаида Доронина', '+7 (239) 570-1585', 'консультант');
INSERT INTO public.sotrudnik_magazina ("Код", "ФИО", "Номер_телефона", "Должность") VALUES (10, 'Анна Куликова', '+7 (882) 628-9148', 'менеджер');
INSERT INTO public.sotrudnik_magazina ("Код", "ФИО", "Номер_телефона", "Должность") VALUES (3, 'Дементьева Эмилия Григорьевна', '+7 (653) 729-0119', 'дизайнер');
INSERT INTO public.sotrudnik_magazina ("Код", "ФИО", "Номер_телефона", "Должность") VALUES (11, 'Чернов Дмитрий Александрович', '+7-967-937-27-07', 'Сортировщик');
INSERT INTO public.sotrudnik_magazina ("Код", "ФИО", "Номер_телефона", "Должность") VALUES (24, 'Sirotov D V', '89639312004', 'sortirovshik');


--
-- TOC entry 4926 (class 0 OID 17087)
-- Dependencies: 221
-- Data for Name: status_zakaza; Type: TABLE DATA; Schema: public; Owner: postgres
--

INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (1, 'Отсортирован', '2024-06-01');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (1, 'Отправлен в город получателя', '2024-06-02');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (1, 'Доставлен в пункт выдачи', '2024-06-02');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (2, 'Отсортирован', '2024-06-02');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (2, 'Отправлен в город получателя', '2024-06-03');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (2, 'Доставлен в пункт выдачи', '2024-06-06');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (3, 'Отсортирован', '2024-06-03');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (3, 'Отправлен в город получателя', '2024-06-04');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (3, 'Доставлен в пункт выдачи', '2024-06-06');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (4, 'Отсортирован', '2024-06-05');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (4, 'Отправлен в город получателя', '2024-06-06');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (4, 'Доставлен в пункт выдачи', '2024-06-08');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (5, 'Отсортирован', '2024-06-08');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (5, 'Отправлен в город получателя', '2024-06-10');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (5, 'Доставлен в пункт выдачи', '2024-06-12');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (6, 'Отсортирован', '2024-06-10');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (6, 'Отправлен в город получателя', '2024-06-11');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (6, 'Доставлен в пункт выдачи', '2024-06-13');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (7, 'Отсортирован', '2024-06-12');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (7, 'Отправлен в город получателя', '2024-06-14');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (7, 'Доставлен в пункт выдачи', '2024-06-16');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (8, 'Отсортирован', '2024-06-15');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (8, 'Отправлен в город получателя', '2024-06-16');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (8, 'Доставлен в пункт выдачи', '2024-06-18');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (9, 'Отсортирован', '2024-06-17');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (9, 'Отправлен в город получателя', '2024-06-19');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (9, 'Доставлен в пункт выдачи', '2024-06-21');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (10, 'Отсортирован', '2024-06-19');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (10, 'Отправлен в город получателя', '2024-06-20');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (10, 'Доставлен в пункт выдачи', '2024-06-22');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (11, 'Отсортирован', '2024-06-21');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (11, 'Отправлен в город получателя', '2024-06-23');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (11, 'Доставлен в пункт выдачи', '2024-06-25');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (12, 'Отсортирован', '2024-06-23');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (12, 'Отправлен в город получателя', '2024-06-24');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (12, 'Доставлен в пункт выдачи', '2024-06-26');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (13, 'Отсортирован', '2024-06-25');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (13, 'Отправлен в город получателя', '2024-06-26');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (13, 'Доставлен в пункт выдачи', '2024-06-28');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (14, 'Отсортирован', '2024-06-27');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (14, 'Отправлен в город получателя', '2024-06-28');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (14, 'Доставлен в пункт выдачи', '2024-06-30');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (15, 'Отсортирован', '2024-06-29');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (15, 'Отправлен в город получателя', '2024-06-30');
INSERT INTO public.status_zakaza ("Номер", "Статус", "Дата") VALUES (15, 'Доставлен в пункт выдачи', '2024-07-02');


--
-- TOC entry 4922 (class 0 OID 16486)
-- Dependencies: 217
-- Data for Name: tovar-katalog; Type: TABLE DATA; Schema: public; Owner: postgres
--

INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('6569314', 'Мультиметр', 'Контрольно-измерительные приборы', 3);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('2223112', 'gtx750 Ti', 'Видеокарты', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1234522', 'gtx1630', 'Видеокарты', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111823', 'GA-970ADS3P', 'Материнские платы', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111900', 'Gigabyte z-470', 'Материнская плата', 1);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111901', 'gtx 1660', 'Видеокарта', 2);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111902', 'AMD ryzen 7 5700g', 'Процессор', 3);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111903', 'Kingston 16gb ddr4', 'Оперативная память', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111904', 'Samsung 860 evo 500gb', 'SSD накопитель', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111905', 'Seagate Barracuda 2tb', 'HDD накопитель', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111906', 'Corsair RM650', 'Блок питания', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111907', 'NZXT H510', 'Корпус для ПК', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111908', 'Logitech g502', 'Игровая мышь', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111909', 'Razer blackwidow v3', 'Игровая клавиатура', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111910', 'Sennheiser hd 560s', 'Наушники', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111911', 'Asus vg249q', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111912', 'MSI optix g271', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111913', 'AOC 24g2', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111914', 'Zowie xl2546k', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111915', 'BenQ xl2546k', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111916', 'ViewSonic xg2402', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111917', 'Acer predator xb273k', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111918', 'Dell s2721dgf', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111919', 'LG 27gn850', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111920', 'Samsung odyssey g7', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111921', 'MSI mpg321ur-qd', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111922', 'Asus rog swift pg279qm', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111923', 'AOC ag273qx', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111924', 'Acer nitro xv272u', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111925', 'ViewSonic elite xg270qc', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111926', 'HP omen x 27', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111927', 'Dell alienware aw2521hf', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111928', 'MSI optix mag274qrf-qd', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111929', 'Asus tuf gaming vg27aq', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111930', 'AOC cq27g2', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111931', 'Acer predator xb271hu', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111932', 'Dell s2721d', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111933', 'LG 27ul850-w', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111934', 'Samsung u28r550', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111935', 'MSI mpg341cqr', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111936', 'Asus rog strix xg43uq', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111937', 'AOC cu34g2x', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111938', 'Acer predator x34 gs', 'Монитор', 4);
INSERT INTO public."tovar-katalog" ("Артикул", "Название", "Тип товара", "Гарантия") VALUES ('1111939', 'ViewSonic vx3218-2kpc-mhd', 'Монитор', 4);


--
-- TOC entry 4925 (class 0 OID 17080)
-- Dependencies: 220
-- Data for Name: zakaz; Type: TABLE DATA; Schema: public; Owner: postgres
--

INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (1, 'Курьер', '2024-06-01', 1, 1);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (2, 'Курьер', '2024-06-02', 2, 1);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (3, 'Самовывоз', '2024-06-02', 3, 2);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (4, 'Самовывоз', '2024-06-03', 1, 3);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (5, 'Курьер', '2024-06-05', 4, 2);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (6, 'Самовывоз', '2024-06-06', 3, 4);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (7, 'Курьер', '2024-06-08', 2, 3);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (8, 'Курьер', '2024-06-10', 1, 3);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (9, 'Самовывоз', '2024-06-12', 4, 3);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (10, 'Самовывоз', '2024-06-13', 3, 1);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (11, 'Курьер', '2024-06-15', 2, 4);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (12, 'Самовывоз', '2024-06-16', 1, 3);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (13, 'Курьер', '2024-06-18', 4, 1);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (14, 'Самовывоз', '2024-06-19', 3, 4);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (15, 'Курьер', '2024-06-20', 2, 2);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (16, 'Курьер', '2024-06-22', 1, 4);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (17, 'Самовывоз', '2024-06-24', 4, 2);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (18, 'Самовывоз', '2024-06-26', 3, 3);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (19, 'Курьер', '2024-06-28', 2, 3);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (20, 'Самовывоз', '2024-06-29', 1, 1);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (21, 'Курьер', '2024-06-30', 4, 4);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (22, 'Самовывоз', '2024-07-01', 3, 2);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (23, 'Курьер', '2024-07-03', 2, 1);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (24, 'Самовывоз', '2024-07-04', 1, 4);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (25, 'Курьер', '2024-07-06', 4, 3);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (26, 'Самовывоз', '2024-07-08', 3, 1);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (27, 'Курьер', '2024-07-10', 2, 2);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (28, 'Курьер', '2024-07-12', 1, 3);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (29, 'Самовывоз', '2024-07-14', 4, 1);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (30, 'Самовывоз', '2024-07-15', 3, 4);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (31, 'Курьер', '2024-07-17', 2, 3);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (32, 'Самовывоз', '2024-07-18', 1, 1);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (33, 'Курьер', '2024-07-19', 4, 4);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (34, 'Курьер', '2024-07-21', 3, 2);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (35, 'Самовывоз', '2024-07-22', 2, 1);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (36, 'Самовывоз', '2024-07-24', 1, 4);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (37, 'Курьер', '2024-07-26', 4, 3);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (38, 'Самовывоз', '2024-07-28', 3, 1);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (39, 'Курьер', '2024-07-30', 2, 2);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (40, 'Курьер', '2024-07-31', 1, 3);
INSERT INTO public.zakaz ("Номер", "Способ получения", "Дата", "Клиент", "Сотрудник") VALUES (41, 'Курьер', '2024-08-01', 5, 1);


--
-- TOC entry 4928 (class 0 OID 17101)
-- Dependencies: 223
-- Data for Name: Поставка; Type: TABLE DATA; Schema: public; Owner: postgres
--

INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (1, '2024-06-01', 1, 1);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (2, '2024-06-02', 2, 4);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (3, '2024-06-02', 5, 1);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (4, '2024-06-03', 3, 2);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (5, '2024-06-05', 1, 3);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (6, '2024-06-06', 2, 1);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (7, '2024-06-08', 5, 4);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (8, '2024-06-10', 1, 2);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (9, '2024-06-12', 3, 3);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (10, '2024-06-13', 2, 4);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (11, '2024-06-15', 5, 1);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (12, '2024-06-16', 1, 3);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (13, '2024-06-18', 2, 2);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (14, '2024-06-20', 5, 4);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (15, '2024-06-22', 1, 1);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (16, '2024-06-24', 3, 3);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (17, '2024-06-26', 2, 1);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (18, '2024-06-28', 5, 4);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (19, '2024-06-29', 1, 2);
INSERT INTO public."Поставка" ("Код", "Дата", "Сотрудник", "Поставщик") VALUES (20, '2024-06-30', 2, 3);


--
-- TOC entry 4927 (class 0 OID 17094)
-- Dependencies: 222
-- Data for Name: Товар в поставке/заказе; Type: TABLE DATA; Schema: public; Owner: postgres
--

INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (1, 2, '4 500,00 ?', '2223112', 1, 'Заказ');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (2, 20, '3 200,00 ?', '2223112', 1, 'Поставка');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (3, 1, '3 500,00 ?', '1111908', 1, 'Заказ');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (4, 5, '2 000,00 ?', '1111900', 2, 'Заказ');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (5, 15, '4 000,00 ?', '1111901', 2, 'Поставка');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (6, 3, '3 000,00 ?', '1111902', 2, 'Заказ');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (7, 10, '2 500,00 ?', '1111903', 3, 'Поставка');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (8, 2, '4 000,00 ?', '1111904', 3, 'Заказ');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (9, 1, '5 000,00 ?', '1111905', 3, 'Поставка');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (10, 4, '3 500,00 ?', '1111906', 4, 'Заказ');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (11, 5, '2 800,00 ?', '1111907', 4, 'Поставка');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (12, 2, '4 500,00 ?', '1111908', 4, 'Заказ');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (13, 3, '3 200,00 ?', '1111909', 5, 'Поставка');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (14, 1, '4 000,00 ?', '1111910', 5, 'Заказ');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (15, 4, '2 500,00 ?', '1111911', 6, 'Поставка');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (16, 5, '3 000,00 ?', '1111912', 6, 'Заказ');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (17, 2, '4 500,00 ?', '1111913', 7, 'Поставка');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (18, 1, '3 200,00 ?', '1111914', 7, 'Заказ');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (19, 3, '4 000,00 ?', '1111915', 8, 'Поставка');
INSERT INTO public."Товар в поставке/заказе" ("ID", "Количество товаров", "Стоимость единицы товара", "Артикул", "Номер заказа/поставки", "Тип операции(заказ/поставка)") VALUES (20, 4, '2 500,00 ?', '1111916', 8, 'Заказ');


--
-- TOC entry 4760 (class 2606 OID 17093)
-- Name: status_zakaza status_zakaza_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.status_zakaza
    ADD CONSTRAINT status_zakaza_pkey PRIMARY KEY ("Номер", "Статус");


--
-- TOC entry 4758 (class 2606 OID 17086)
-- Name: zakaz zakaz_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.zakaz
    ADD CONSTRAINT zakaz_pkey PRIMARY KEY ("Номер");


--
-- TOC entry 4754 (class 2606 OID 16504)
-- Name: garantiya Гарантия_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.garantiya
    ADD CONSTRAINT "Гарантия_pkey" PRIMARY KEY ("Код");


--
-- TOC entry 4748 (class 2606 OID 16425)
-- Name: klient Клиент_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.klient
    ADD CONSTRAINT "Клиент_pkey" PRIMARY KEY ("Код");


--
-- TOC entry 4764 (class 2606 OID 17105)
-- Name: Поставка Поставка_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Поставка"
    ADD CONSTRAINT "Поставка_pkey" PRIMARY KEY ("Код");


--
-- TOC entry 4756 (class 2606 OID 16516)
-- Name: postavshik Поставщик_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.postavshik
    ADD CONSTRAINT "Поставщик_pkey" PRIMARY KEY ("Код");


--
-- TOC entry 4750 (class 2606 OID 16432)
-- Name: sotrudnik_magazina Сотрудник магазина_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.sotrudnik_magazina
    ADD CONSTRAINT "Сотрудник магазина_pkey" PRIMARY KEY ("Код");


--
-- TOC entry 4762 (class 2606 OID 17100)
-- Name: Товар в поставке/заказе Товар в поставке/заказе_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Товар в поставке/заказе"
    ADD CONSTRAINT "Товар в поставке/заказе_pkey" PRIMARY KEY ("ID");


--
-- TOC entry 4752 (class 2606 OID 16492)
-- Name: tovar-katalog Товар-каталог_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."tovar-katalog"
    ADD CONSTRAINT "Товар-каталог_pkey" PRIMARY KEY ("Артикул");


--
-- TOC entry 4769 (class 2606 OID 17106)
-- Name: Товар в поставке/заказе fk11; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Товар в поставке/заказе"
    ADD CONSTRAINT fk11 FOREIGN KEY ("Номер заказа/поставки") REFERENCES public.zakaz("Номер") NOT VALID;


--
-- TOC entry 4770 (class 2606 OID 17111)
-- Name: Товар в поставке/заказе fk12; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Товар в поставке/заказе"
    ADD CONSTRAINT fk12 FOREIGN KEY ("Номер заказа/поставки") REFERENCES public."Поставка"("Код") NOT VALID;


--
-- TOC entry 4771 (class 2606 OID 17116)
-- Name: Товар в поставке/заказе fk13; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Товар в поставке/заказе"
    ADD CONSTRAINT fk13 FOREIGN KEY ("Артикул") REFERENCES public."tovar-katalog"("Артикул") NOT VALID;


--
-- TOC entry 4772 (class 2606 OID 17121)
-- Name: Поставка fk13; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Поставка"
    ADD CONSTRAINT fk13 FOREIGN KEY ("Сотрудник") REFERENCES public.sotrudnik_magazina("Код") NOT VALID;


--
-- TOC entry 4773 (class 2606 OID 17126)
-- Name: Поставка fk14; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Поставка"
    ADD CONSTRAINT fk14 FOREIGN KEY ("Поставщик") REFERENCES public.postavshik("Код") NOT VALID;


--
-- TOC entry 4768 (class 2606 OID 17131)
-- Name: status_zakaza fk15; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.status_zakaza
    ADD CONSTRAINT fk15 FOREIGN KEY ("Номер") REFERENCES public.zakaz("Номер") NOT VALID;


--
-- TOC entry 4766 (class 2606 OID 17186)
-- Name: zakaz fk16; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.zakaz
    ADD CONSTRAINT fk16 FOREIGN KEY ("Клиент") REFERENCES public.klient("Код") ON DELETE CASCADE;


--
-- TOC entry 4767 (class 2606 OID 17181)
-- Name: zakaz fk17; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.zakaz
    ADD CONSTRAINT fk17 FOREIGN KEY ("Сотрудник") REFERENCES public.sotrudnik_magazina("Код") ON DELETE CASCADE;


--
-- TOC entry 4765 (class 2606 OID 16505)
-- Name: tovar-katalog fkey6; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."tovar-katalog"
    ADD CONSTRAINT fkey6 FOREIGN KEY ("Гарантия") REFERENCES public.garantiya("Код") NOT VALID;


-- Completed on 2024-11-16 15:44:27

--
-- PostgreSQL database dump complete
--

